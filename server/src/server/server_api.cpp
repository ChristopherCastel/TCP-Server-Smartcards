#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "nlohmann/json.hpp"
#include "plog/include/plog/Log.h"
#include "plog/include/plog/Appenders/ColorConsoleAppender.h"

#include "server_api.h"
#include "server_engine.h"
#include "../constants/request_code.h"
#include "../constants/response_packet.h"

namespace server {

ResponsePacket ServerAPI::initServer(std::string path) {
	return engine.initServer(path);
}

ResponsePacket ServerAPI::startServer() {
	return engine.startListening();
}

ResponsePacket ServerAPI::listClients() {
	return engine.listClients();
}

ResponsePacket ServerAPI::sendCommand(int id_client, std::string command) {
	return engine.handleRequest(id_client, REQ_COMMAND);
}

ResponsePacket ServerAPI::restartTarget(int id_client) {
	return engine.handleRequest(id_client, REQ_RESTART);
}

ResponsePacket ServerAPI::echoClient(int id_client) {
	return engine.handleRequest(id_client, REQ_ECHO);
}

ResponsePacket ServerAPI::diagClient(int id_client) {
	return engine.handleRequest(id_client, REQ_DIAG);
}

ResponsePacket ServerAPI::stopServer() {
	ResponsePacket response = engine.stopAllClients();
	return response;
}

}  // namespace server

