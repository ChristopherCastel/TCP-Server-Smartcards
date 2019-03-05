/*
 * terminal_layer.h
 *
 *  Created on: 26 Feb 2019
 *      Author: Castel Christopher
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

	virtual ResponsePacket init() = 0;

	virtual ResponsePacket sendCommand(unsigned char command[], DWORD command_length) = 0;

	virtual ResponsePacket diag() = 0;

	virtual ResponsePacket disconnect() = 0;

	virtual ResponsePacket isAlive() = 0;

};

} /* namespace client */

#endif /* TERMINAL_LAYER_H_ */
