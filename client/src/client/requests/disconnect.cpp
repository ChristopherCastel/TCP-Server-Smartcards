/*
 * disconnect.cpp
 *
 *  Created on: 01 Mar 2019
 *  Author: STMicroelectronics
 */

#include <winsock2.h>
#include "client/requests/disconnect.h"
#include "client/client_engine.h"
#include "plog/include/plog/Log.h"

namespace client {

ResponsePacket Disconnect::run(ITerminalLayer* terminal, ClientEngine* client_engine, char unsigned command[], DWORD command_length) {
	return client_engine->disconnectClient();
}

} /* namespace client */
