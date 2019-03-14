/*
 * dll_client_api_wrapper.cpp
 *
 *  Created on: 08 Mar 2019
 *  Author: Castel Christopher
 */

#include "client/dll_client_api_wrapper.h"
#include "client/client_api.h"
#include "terminal/flyweight_terminal_factory.h"
#include "terminal/terminals/terminal_pcsc.h"
#include "client/requests/request.h"
#include "client/requests/command.h"
#include "client/requests/diag.h"
#include "client/requests/disconnect.h"
#include "client/requests/echo.h"
#include "constants/request_code.h"

#include <iostream>

using namespace client;

ADDAPI void setCallback(Callback handler) {
	Handler = handler;
}

ADDAPI client::ClientAPI* createClientAPI() {
	ClientAPI* client = new client::ClientAPI(Handler);
	return client;
}

ADDAPI void disposeClientAPI(client::ClientAPI* client) {
	delete client;
	client = NULL;
}

ADDAPI void disconnectClient(client::ClientAPI* client, ResponseDLL& response_packet_dll) {
	ResponsePacket response_packet = client->disconnectClient();
	responsePacketForDll(response_packet, response_packet_dll);
}

ADDAPI void initClient(client::ClientAPI* client, ResponseDLL& response_packet_dll) {
	// config available terminal factories
	FlyweightTerminalFactory available_terminals;
	available_terminals.addFactory("PCSC", new PCSCFactory());
	// config all requests the client can handle
	FlyweightRequests available_requests;
	available_requests.addRequest(REQ_COMMAND, new Command());
	available_requests.addRequest(REQ_DIAG, new Diag());
	available_requests.addRequest(REQ_DISCONNECT, new Disconnect());
	available_requests.addRequest(REQ_ECHO, new Echo());

	ResponsePacket response_packet = client->initClient("./config/init.json", available_terminals, available_requests);
	responsePacketForDll(response_packet, response_packet_dll);
}

ADDAPI void loadAndListReaders(ClientAPI* client, ResponseDLL& response_packet_dll) {
	ResponsePacket response_packet = client->loadAndListReaders();
	responsePacketForDll(response_packet, response_packet_dll);
}

ADDAPI void connectClient(client::ClientAPI* client, int key, ResponseDLL& response_packet_dll) {
	ResponsePacket response_packet = client->connectClient(key);
	responsePacketForDll(response_packet, response_packet_dll);
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
