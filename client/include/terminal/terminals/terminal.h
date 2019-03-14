/*
 * terminal_layer.h
 *
 *  Created on: 26 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Interface for implementing terminal layers such as PCSC.
 */

#ifndef TERMINAL_LAYER_H_
#define TERMINAL_LAYER_H_

#include "windows.h"
#include "../../constants/response_packet.h"

namespace client {

class ITerminalLayer {
public:
	ITerminalLayer() {};
	virtual ~ITerminalLayer() {};

	/**
	 * init - initialize the terminal.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	virtual ResponsePacket init() = 0;

	/**
	 * loadAndListReaders - load and list available readers.
	 * The "response" field contains the id and name of each reader.
	 * The "response" field will be formatted this way: ReaderID|ReaderName|...|...
	 * @return a ResponsePacket struct containing either the list of readers or error codes (under 0) and error descriptions.
	 */
	virtual ResponsePacket loadAndListReaders() = 0;

	/**
	 * connect - connect to the given reader.
	 * @param key the key corresponding to a reader.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	virtual ResponsePacket connect(int key) = 0;

	/**
	 * init - initialize the terminal.
	 * @param command the command to be sent to the smartcard.
	 * @param command_length the length of the given command.
	 * @return a ResponsePacket struct containing either the smartcard's response or error codes and error descriptions in case of error.
	 */
	virtual ResponsePacket sendCommand(unsigned char command[], DWORD command_length) = 0;

	/**
	 * diag - diagnose the used terminal.
	 * The diagnostic will be in the field "response" of the ResponsePacket structure.
	 * The diagnostic will be formatted this way: TheReaderName|TheReaderStatus|TheReaderProtocolUsed
	 * @return a ResponsePacket struct containing either the data or error codes and error descriptions.
	 */
	virtual ResponsePacket diag() = 0;

	/**
	 * disconnect - disconnect the terminal.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	virtual ResponsePacket disconnect() = 0;

	/**
	 * isAlive - send a valid packet to the terminal to check whether it is responding.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	virtual ResponsePacket isAlive() = 0;
};

} /* namespace client */

#endif /* TERMINAL_LAYER_H_ */
