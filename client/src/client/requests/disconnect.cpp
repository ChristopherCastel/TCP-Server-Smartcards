/*
 * disconnect.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#include "disconnect.h"
#include "../client_engine.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Disconnect::run(ITerminalLayer* terminal, ClientEngine* client_engine) {
	LOG_INFO << "Request \"disconnect\" is being processed";
	client_engine->setStopFlag(true);
	return terminal->disconnect();
}

} /* namespace client */
