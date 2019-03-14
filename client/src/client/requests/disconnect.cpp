/*
 * disconnect.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#include "client/requests/disconnect.h"
#include "client/client_engine.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Disconnect::run(ITerminalLayer* terminal, ClientEngine* client_engine, char unsigned command[], DWORD command_length) {
	LOG_INFO << "Request \"disconnect\" is being processed";
	client_engine->setStopFlag(true);
	return terminal->disconnect();
}

} /* namespace client */
