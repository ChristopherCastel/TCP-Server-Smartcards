/*
 * client_api.cpp
 *
 *  Created on: 26 Feb 2019
 *  Author: STMicroelectronics
 */

#include <atomic>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "plog/include/plog/Log.h"
#include "plog/include/plog/Appenders/ColorConsoleAppender.h"

#include "client/client_api.h"

namespace client {

ClientAPI::~ClientAPI() {
	delete engine;
}

ResponsePacket ClientAPI::initClient(std::string path, FlyweightTerminalFactory available_terminals, FlyweightRequests available_requests) {
	return engine->initClient(path, available_terminals, available_requests);
}

ResponsePacket ClientAPI::connectClient(int terminal_key, const char* ip, const char* port) {
	return engine->connectClient(terminal_key, ip, port);
}

ResponsePacket ClientAPI::disconnectClient() {
	return engine->disconnectClient();
}

ResponsePacket ClientAPI::loadAndListReaders() {
	return engine->loadAndListReaders();
}

} /* namespace client */
