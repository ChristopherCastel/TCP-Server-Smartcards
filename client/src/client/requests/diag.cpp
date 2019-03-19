/*
 * diag.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: STMicroelectronics
 */

#include "client/requests/diag.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Diag::run(ITerminalLayer* terminal, ClientEngine* client_engine, char unsigned command[], DWORD command_length) {
	LOG_INFO << "Request \"diag\" is being processed";
	return terminal->diag();
}

} /* namespace client */
