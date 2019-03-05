/*
 * pcsc.h
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef TERMINAL_TERMINALS_TERMINAL_PCSC_H_
#define TERMINAL_TERMINALS_TERMINAL_PCSC_H_

#include <winscard.h>

#include "terminal.h"
#include "../../constants/response_packet.h"

typedef unsigned char BYTE;


namespace client {

class TerminalPCSC: public ITerminalLayer {
private:
	SCARDCONTEXT hContext;
	LPTSTR mszReaders;
	SCARDHANDLE hCard;
	DWORD dwReaders, dwActiveProtocol, dwRecvLength;
	SCARD_IO_REQUEST pioSendPci;
	BYTE pbRecvBuffer[258];
public:
	TerminalPCSC() {};

	~TerminalPCSC() {};

	ResponsePacket init();

	ResponsePacket sendCommand(unsigned char command[], DWORD command_length);

	ResponsePacket diag();

	ResponsePacket disconnect();

	ResponsePacket isAlive();

	std::string errorToString(LONG error);

	ResponsePacket handleErrorResponse(std::string context_message, LONG error);

	std::string hexToString(unsigned char hex[], DWORD length);
};

} /* namespace client */

#endif /* TERMINAL_TERMINALS_TERMINAL_PCSC_H_ */
