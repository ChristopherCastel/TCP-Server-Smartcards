/*
 * diag.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#include "diag.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Diag::run(ITerminalLayer* terminal, ClientEngine* client_engine) {
	LOG_INFO << "Request \"diag\" is being processed";
	return terminal->diag();
}

} /* namespace client */
