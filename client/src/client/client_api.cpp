/*
 * client_api.cpp
 *
 *  Created on: 26 Feb 2019
 *      Author: Castel Christopher
 */

#include <atomic>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "plog/include/plog/Log.h"
#include "plog/include/plog/Appenders/ColorConsoleAppender.h"

#include "client_api.h"

namespace client {

ResponsePacket ClientAPI::initClient(std::string path, FlyweightTerminalFactory available_terminals, FlyweightRequests available_requests) {
	return engine.initClient(path, available_terminals, available_requests);
}

ResponsePacket ClientAPI::connectClient() {
	return engine.connectClient();
}

ResponsePacket ClientAPI::disconnectClient() {
	return engine.disconnectClient();
}

} /* namespace client */
