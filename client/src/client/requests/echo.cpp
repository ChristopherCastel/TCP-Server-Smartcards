/*
 * echo.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#include "echo.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Echo::run(ITerminalLayer* terminal, ClientEngine* client_engine) {
	LOG_INFO << "Request \"echo\" is being processed";
	return terminal->isAlive();
}

} /* namespace client */
