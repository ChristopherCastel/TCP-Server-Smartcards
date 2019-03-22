#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "nlohmann/json.hpp"
#include "plog/include/plog/Log.h"
#include "plog/include/plog/Appenders/ColorConsoleAppender.h"

#include "server/server_api.h"
#include "server/server_engine.h"
#include "constants/request_code.h"
#include "constants/response_packet.h"

namespace server {

ResponsePacket ServerAPI::initServer(std::string path) {
	ResponsePacket resp = engine->initServer(path);
	return resp;
}

ResponsePacket ServerAPI::startServer() {
	return engine->startListening();
}

ResponsePacket ServerAPI::listClients() {
	return engine->listClients();
}

ResponsePacket ServerAPI::sendCommand(int id_client, std::string command) {
	return engine->handleRequest(id_client, REQ_COMMAND, command);
}

ResponsePacket ServerAPI::restartTarget(int id_client) {
	return engine->handleRequest(id_client, REQ_RESTART);
}

ResponsePacket ServerAPI::echoClient(int id_client) {
	return engine->handleRequest(id_client, REQ_ECHO);
}

ResponsePacket ServerAPI::diagClient(int id_client) {
	return engine->handleRequest(id_client, REQ_DIAG);
}

ResponsePacket ServerAPI::stopClient(int id_client) {
	return engine->handleRequest(id_client, REQ_DISCONNECT);
}

ResponsePacket ServerAPI::stopServer() {
	return engine->stopAllClients();
}

}  // namespace server

