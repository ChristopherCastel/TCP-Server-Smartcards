/*
 * command.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: STMicroelectronics
 */

#include <winsock2.h>
#include <windows.h>
#include "client/requests/command.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Command::run(ITerminalLayer* terminal, ClientEngine* client_engine, char unsigned command[], DWORD command_length) {
	LOG_INFO << "Request \"command\" is being processed";
	return terminal->sendCommand(command, command_length);
}

} /* namespace client */
