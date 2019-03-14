/*
 * echo.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#include "client/requests/echo.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Echo::run(ITerminalLayer* terminal, ClientEngine* client_engine, char unsigned command[], DWORD command_length) {
	LOG_INFO << "Request \"echo\" is being processed";
	return terminal->isAlive();
}

} /* namespace client */
