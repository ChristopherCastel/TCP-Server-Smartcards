/*
 * command.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#include <winsock2.h>
#include <windows.h>
#include "command.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Command::run(ITerminalLayer* terminal, ClientEngine* client_engine) {
	LOG_INFO << "Request \"command\" is being processed";
	unsigned char command[] = { 0x00 };
	DWORD command_length = sizeof(command);

	return terminal->sendCommand(command, command_length);
}

} /* namespace client */
