/*
 * pcsc.cpp
 *
 *  Created on: 28 Feb 2019
 *  Author: STMicroelectronics
 */

#include <iostream>
#include <winscard.h>
#include <map>

#include "terminal/terminals/terminal_pcsc.h"
#include "constants/response_packet.h"
#include "utils/type_converter.h"
#include "plog/include/plog/Log.h"

namespace client {

TerminalPCSC::~TerminalPCSC() {
	if (SCardFreeMemory(hContext, mszReaders) != SCARD_S_SUCCESS) {
		LOG_DEBUG << "Failed to call SCardFreeMemory() " << "[card:" << hCard << "][mszReaders:" << mszReaders << "]";
	}

	if (SCardReleaseContext(hContext) != SCARD_S_SUCCESS) {
		LOG_DEBUG << "Failed to call SCardReleaseContext() " << "[card:" << hCard << "][hContext:" << hContext << "]";
	}
}

ResponsePacket TerminalPCSC::init() {
	ResponsePacket response;
	LONG resp;
	if ((resp = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext)) != SCARD_S_SUCCESS) {
		LOG_DEBUG << "Failed to call SCardEstablishContext() [error:" << errorToString(resp) << "]"
				  << "[dwScope:" << SCARD_SCOPE_SYSTEM << "][pvReserved1:" << NULL << "][pvReserved1:" << NULL << "][hContext:" << hContext << "]";
		return handleErrorResponse("Failed to establish context", resp);
	}

	LOG_INFO << "Terminal PCSC initialized";
	return response;
}

ResponsePacket TerminalPCSC::loadAndListReaders() {
	ResponsePacket response;
	LONG resp;

	dwReaders = SCARD_AUTOALLOCATE;
	if ((resp = SCardListReaders(hContext, NULL, (LPTSTR) &mszReaders, &dwReaders)) != SCARD_S_SUCCESS) {
		LOG_DEBUG << "Failed to call SCardListReaders() [error:" << errorToString(resp) << "]"
				<< "[hContext:" << hContext << "][mszGroups:" << NULL << "][mszReaders:" << mszReaders << "][dwReaders:" << dwReaders << "]";
		return handleErrorResponse("Failed to list readers", resp);
	}

	LPTSTR pReader = mszReaders;
	std::string list_readers;
	int i = 0;
	while ('\0' != *pReader) {
		LOG_DEBUG << "Loaded reader: " << pReader;
		list_readers += std::to_string(i) + "|" + std::string((const char*) pReader) + "|";
		available_readers.insert(std::make_pair(i, pReader));
		pReader = pReader + strlen((const char*) pReader) + 1;
		i++;
	}

	LOG_INFO << "Readers loaded";
	response.response = list_readers;
	return response;
}

ResponsePacket TerminalPCSC::connect(int key) {
	ResponsePacket response;
	LONG resp;

	LPCSTR szReader = available_readers.at(key);
	LOG_INFO << "Trying to connect: " << szReader;

	if ((resp = SCardConnect(hContext, szReader, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol)) != SCARD_S_SUCCESS) {
		LOG_DEBUG << "Failed to call SCardConnect() " << "[error:" << errorToString(resp) << "]"
				  << "[hContext:" << hContext << "][szReader:" << szReader << "][dwShareMode:" << SCARD_SHARE_SHARED << "]"
				  << "[dwPreferredProtocols:" << 0 << "][hCard:" << hCard << "][dwActiveProtocol:" << dwActiveProtocol << "]";
		return handleErrorResponse("Failed to connect", resp);
	}

	switch (dwActiveProtocol) {
	case SCARD_PROTOCOL_T0:
		pioSendPci = *SCARD_PCI_T0;
		break;

	case SCARD_PROTOCOL_T1:
		pioSendPci = *SCARD_PCI_T1;
		break;
	}

	LOG_DEBUG << "Reader connected: " << szReader;
	return response;
}

ResponsePacket TerminalPCSC::sendCommand(unsigned char command[], DWORD command_length) {
	LONG resp;
	std::string strCommand = utils::unsignedCharToString(command, command_length);

	LOG_INFO << "Terminal PCSC received APDU command: " << strCommand;
	dwRecvLength = sizeof(pbRecvBuffer);
	if ((resp = SCardTransmit(hCard, &pioSendPci, command, command_length, NULL, pbRecvBuffer, &dwRecvLength)) != SCARD_S_SUCCESS) {
		LOG_DEBUG << "Failed to call SCardTransmit() [error:" << errorToString(resp) << "]"
				  << "[card:" << hCard << "][pbSendBuffer:" << command << "][cbSendLength:" << command_length << "]"
				  << "[recvbuffer:" << pbRecvBuffer << "][recvlength:" << dwRecvLength << "]";
		return handleErrorResponse("Failed to transmit", resp);
	}
	std::string responseAPDU =  utils::unsignedCharToString(pbRecvBuffer, dwRecvLength);
	LOG_INFO << "Terminal PCSC sent APDU response: " << responseAPDU;

	ResponsePacket response = { .response = responseAPDU };
	return response;
}

ResponsePacket TerminalPCSC::isAlive() {
	unsigned char command[] = { 0x00, 0x00, 0x00, 0x00 };
	return sendCommand(command, sizeof(command));
}

ResponsePacket TerminalPCSC::diag() {
	ResponsePacket response;
	LONG resp;
	CHAR szReader[200];
	DWORD cch = 200;
	BYTE bAttr[32];
	DWORD cByte = 32;
	DWORD dwState, dwProtocol;

	if ((resp = SCardStatus(hCard, szReader, &cch, &dwState, &dwProtocol, (LPBYTE) &bAttr, &cByte)) != SCARD_S_SUCCESS) {
		LOG_DEBUG << "Failed to call SCardStatus()  [error:" << errorToString(resp) << "]"
				  << "[card:" << hCard << "][szReader:" << szReader << "][cch:" << cch << "][dwState:" << dwState << "][dwProtocol:" << dwProtocol << "][bAttr:" << bAttr << "][cByte:" << cByte <<"]";
		return handleErrorResponse("Failed to retrieve card status", resp);
	}

	std::string status;
	switch (dwState) {
	case SCARD_ABSENT:
		status = "Card absent.";
		break;
	case SCARD_PRESENT:
		status = "Card present.";
		break;
	case SCARD_SWALLOWED:
		status = "Card swallowed.";
		break;
	case SCARD_POWERED:
		status = "Card has power.";
		break;
	case SCARD_NEGOTIABLE:
		status = "Card reset and waiting PTS negotiation.";
		break;
	case SCARD_SPECIFIC:
		status = "Card has specific communication protocols set.";
		break;
	default:
		status = "Unknown or unexpected card state.";
		break;
	}

	std::string protocol;
	switch (dwProtocol) {
	case SCARD_PROTOCOL_RAW:
		protocol = "The Raw Transfer protocol is in use.";
		break;
	case SCARD_PROTOCOL_T0:
		protocol = "The ISO 7816/3 T=0 protocol is in use.";
		break;
	case SCARD_PROTOCOL_T1:
		protocol = "The ISO 7816/3 T=1 protocol is in use.";
		break;
	default:
		protocol = "Unknown or unexpected protocol in use.";
	}

	std::string readers(szReader);

	response.response = "Readers: " + readers + " | Status: " + status + " | Protocol: " + protocol;
	return response;
}

ResponsePacket TerminalPCSC::disconnect() {
	ResponsePacket response;
	LONG resp;

	if ((resp = SCardDisconnect(hCard, SCARD_LEAVE_CARD)) != SCARD_S_SUCCESS) {
		LOG_DEBUG << "Failed to call SCardDisconnect() "
				  << "[card:" << hCard << "][dwDisposition:" << SCARD_LEAVE_CARD << "]";
		return handleErrorResponse("Failed to disconnect", resp);
	}

	LOG_INFO << "Terminal PCSC disconnected successfully";
	return response;
}

std::string TerminalPCSC::errorToString(LONG error) {
	switch (error) {
	case ERROR_BROKEN_PIPE:
		return "The client attempted a smart card operation in a remote session, such as a client session running on a terminal server, and the operating system in use does not support smart card redirection.";
	case SCARD_E_BAD_SEEK:
		return "An error occurred in setting the smart card file object pointer.";
	case SCARD_E_CANCELLED:
		return "The action was canceled by an case SCARDCancel request.";
	case SCARD_E_CANT_DISPOSE:
		return "The system could not dispose of the media in the requested manner.";
	case SCARD_E_CARD_UNSUPPORTED:
		return "The smart card does not meet minimal requirements for support.";
	case SCARD_E_CERTIFICATE_UNAVAILABLE:
		return "The requested certificate could not be obtained.";
	case SCARD_E_COMM_DATA_LOST:
		return "A communications error with the smart card has been detected. ";
	case SCARD_E_DIR_NOT_FOUND:
		return "The specified directory does not exist in the smart card.";
	case SCARD_E_DUPLICATE_READER:
		return "The reader driver did not produce a unique reader name.";
	case SCARD_E_FILE_NOT_FOUND:
		return "The specified file does not exist in the smart card.";
	case SCARD_E_ICC_CREATEORDER:
		return "The requested order of object creation is not supported.";
	case SCARD_E_ICC_INSTALLATION:
		return "No primary provider can be found for the smart card.";
	case SCARD_E_INSUFFICIENT_BUFFER:
		return "The data buffer for returned data is too small for the returned data.";
	case SCARD_E_INVALID_ATR:
		return "An ATR string obtained from the registry is not a valid ATR string.";
	case SCARD_E_INVALID_CHV:
		return "The supplied PIN is incorrect.";
	case SCARD_E_INVALID_HANDLE:
		return "The supplied handle was not valid.";
	case SCARD_E_INVALID_PARAMETER:
		return "One or more of the supplied parameters could not be properly interpreted.";
	case SCARD_E_INVALID_TARGET:
		return "Registry startup information is missing or not valid.";
	case SCARD_E_INVALID_VALUE:
		return "One or more of the supplied parameter values could not be properly interpreted.";
	case SCARD_E_NO_ACCESS:
		return "Access is denied to the file.";
	case SCARD_E_NO_DIR:
		return "The supplied path does not represent a smart card directory.";
	case SCARD_E_NO_FILE:
		return "The supplied path does not represent a smart card file.";
	case SCARD_E_NO_KEY_CONTAINER:
		return "The requested key container does not exist on the smart card.";
	case SCARD_E_NO_MEMORY:
		return "Not enough memory available to complete this command.";
	case SCARD_E_NO_READERS_AVAILABLE:
		return "No smart card reader is available.";
	case SCARD_E_NO_SERVICE:
		return "The smart card resource manager is not running.";
	case SCARD_E_NO_SMARTCARD:
		return "The operation requires a smart card, but no smart card is currently in the device.";
	case SCARD_E_NO_SUCH_CERTIFICATE:
		return "The requested certificate does not exist.";
	case SCARD_E_NOT_READY:
		return "The reader or card is not ready to accept commands.";
	case SCARD_E_NOT_TRANSACTED:
		return "An attempt was made to end a nonexistent transaction.";
	case SCARD_E_PCI_TOO_SMALL:
		return "The PCI receive buffer was too small.";
	case SCARD_E_PROTO_MISMATCH:
		return "The requested protocols are incompatible with the protocol currently in use with the card.";
	case SCARD_E_READER_UNAVAILABLE:
		return "The specified reader is not currently available for use.";
	case SCARD_E_READER_UNSUPPORTED:
		return "The reader driver does not meet minimal requirements for support.";
	case SCARD_E_SERVER_TOO_BUSY:
		return "The smart card resource manager is too busy to complete this operation.";
	case SCARD_E_SERVICE_STOPPED:
		return "The smart card resource manager has shut down.";
	case SCARD_E_SHARING_VIOLATION:
		return "The smart card cannot be accessed because of other outstanding connections.";
	case SCARD_E_SYSTEM_CANCELLED:
		return "The action was canceled by the system, presumably to log off or shut down.";
	case SCARD_E_TIMEOUT:
		return "The user-specified time-out value has expired.";
	case SCARD_E_UNEXPECTED:
		return "An unexpected card error has occurred.";
	case SCARD_E_UNKNOWN_CARD:
		return "The specified smart card name is not recognized.";
	case SCARD_E_UNKNOWN_READER:
		return "The specified reader name is not recognized.";
	case SCARD_E_UNKNOWN_RES_MNG:
		return "An unrecognized error code was returned.";
	case SCARD_E_UNSUPPORTED_FEATURE:
		return "This smart card does not support the requested feature.";
	case SCARD_E_WRITE_TOO_MANY:
		return "An attempt was made to write more data than would fit in the target object.";
	case SCARD_F_COMM_ERROR:
		return "An internal communications error has been detected.";
	case SCARD_F_INTERNAL_ERROR:
		return "An internal consistency check failed.";
	case SCARD_F_UNKNOWN_ERROR:
		return "An internal error has been detected, but the source is unknown.";
	case SCARD_F_WAITED_TOO_LONG:
		return "An internal consistency timer has expired.";
	case SCARD_P_SHUTDOWN:
		return "The operation has been aborted to allow the server application to exit.";
	case SCARD_S_SUCCESS:
		return "No error was encountered.";
	case SCARD_W_CANCELLED_BY_USER:
		return "The action was canceled by the user.";
	case SCARD_W_CACHE_ITEM_NOT_FOUND:
		return "The requested item could not be found in the cache.";
	case SCARD_W_CACHE_ITEM_STALE:
		return "The requested cache item is too old and was deleted from the cache.";
	case SCARD_W_CARD_NOT_AUTHENTICATED:
		return "No PIN was presented to the smart card.";
	case SCARD_W_CHV_BLOCKED:
		return "The card cannot be accessed because the maximum number of PIN entry attempts has been reached.";
	case SCARD_W_EOF:
		return "The end of the smart card file has been reached.";
	case SCARD_W_REMOVED_CARD:
		return "The smart card has been removed, so further communication is not possible.";
	case SCARD_W_RESET_CARD:
		return "The smart card was reset.";
	case SCARD_W_SECURITY_VIOLATION:
		return "Access was denied because of a security violation.";
	case SCARD_W_UNPOWERED_CARD:
		return "Power has been removed from the smart card, so that further communication is not possible.";
	case SCARD_W_UNRESPONSIVE_CARD:
		return "The smart card is not responding to a reset.";
	case SCARD_W_UNSUPPORTED_CARD:
		return "The reader cannot communicate with the card, due to ATR string configuration conflicts.";
	case SCARD_W_WRONG_CHV:
		return "The card cannot be accessed because the wrong PIN was presented.";
	default:
		return "Unknown error.";
	}
}

ResponsePacket TerminalPCSC::handleErrorResponse(std::string context_message, LONG error) {
	std::string message = context_message + ": " + errorToString(error);
	ResponsePacket response = { .err_terminal_code = error, .err_terminal_description = message };
	return response;
}

} /* namespace client */
