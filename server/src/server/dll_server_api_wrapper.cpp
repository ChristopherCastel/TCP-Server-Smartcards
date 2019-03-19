/*
 * dll_client_api_wrapper.cpp
 *
 *  Created on: 08 Mar 2019
 *  Author: STMicroelectronics
 */

#include "server/server_api.h"
#include "constants/request_code.h"
#include "server/dll_server_api_wrapper.h"

#include <iostream>

using namespace server;

ADDAPI server::ServerAPI* createServerAPI() {
	ServerAPI* server = new ServerAPI();
	return server;
}

ADDAPI void initServer(server::ServerAPI* server, ResponseDLL& response_packet) {
	ResponsePacket response = server->initServer("./config/init.json");
	responsePacketForDll(response, response_packet);
}

ADDAPI void startServer(server::ServerAPI* server, ResponseDLL& response_packet) {
	ResponsePacket response = server->startServer();
	responsePacketForDll(response, response_packet);
}

ADDAPI void listClients(server::ServerAPI* server, ResponseDLL& response_packet) {
	ResponsePacket response = server->listClients();
	responsePacketForDll(response, response_packet);
}

ADDAPI void echoClient(server::ServerAPI* server, int id_client, ResponseDLL& response_packet) {
	ResponsePacket response = server->echoClient(id_client);
	responsePacketForDll(response, response_packet);
}

ADDAPI void diagClient(server::ServerAPI* server, int id_client, ResponseDLL& response_packet) {
	ResponsePacket response = server->diagClient(id_client);
	responsePacketForDll(response, response_packet);
}

ADDAPI void sendCommand(server::ServerAPI* server, int id_client, char* command, ResponseDLL& response_packet) {
	ResponsePacket response = server->sendCommand(id_client, command);
	responsePacketForDll(response, response_packet);
}

ADDAPI void restartTarget(server::ServerAPI* server, int id_client, ResponseDLL& response_packet) {
	ResponsePacket response = server->restartTarget(id_client);
	responsePacketForDll(response, response_packet);
}

ADDAPI void stopClient(server::ServerAPI* server, int id_client, ResponseDLL& response_packet) {
	ResponsePacket response = server->stopClient(id_client);
	responsePacketForDll(response, response_packet);
}

ADDAPI void stopServer(server::ServerAPI* server, ResponseDLL& response_packet) {
	ResponsePacket response = server->startServer();
	responsePacketForDll(response, response_packet);
}

ADDAPI void disposeServerAPI(server::ServerAPI* server) {
	delete server;
}

void responsePacketForDll(ResponsePacket response_packet, ResponseDLL& response_packet_dll) {
	strcpy(response_packet_dll.response, response_packet.response.c_str());

	response_packet_dll.err_server_code = response_packet.err_server_code;
	strcpy(response_packet_dll.err_server_description, response_packet.err_server_description.c_str());

	response_packet_dll.err_client_code = response_packet.err_client_code;
	strcpy(response_packet_dll.err_client_description, response_packet.err_client_description.c_str());

	response_packet_dll.err_terminal_code = response_packet.err_terminal_code;
	strcpy(response_packet_dll.err_terminal_description, response_packet.err_terminal_description.c_str());

	response_packet_dll.err_card_code = response_packet.err_card_code;
	strcpy(response_packet_dll.err_card_description, response_packet.err_card_description.c_str());
}
