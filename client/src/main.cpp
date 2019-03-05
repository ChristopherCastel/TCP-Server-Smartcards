/*
 * main.cpp
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#include "constants/request_code.h"
#include "client/client_api.h"
#include "client/requests/command.h"
#include "client/requests/diag.h"
#include "client/requests/disconnect.h"
#include "client/requests/echo.h"
#include "client/requests/request.h"
#include "client/requests/flyweight_requests.h"
#include "terminal/flyweight_terminal_factory.h"
#include "terminal/terminals/terminal_pcsc.h"

#include "plog/include/plog/Log.h"

using namespace client;

int __cdecl main(void) {
	// config available terminal factories
	FlyweightTerminalFactory available_terminals;
	available_terminals.addFactory("PCSC", new PCSCFactory());

	// config all requests the client can handle
	FlyweightRequests available_requests;
	available_requests.addRequest(REQ_COMMAND, new Command());
	available_requests.addRequest(REQ_DIAG, new Diag());
	available_requests.addRequest(REQ_DISCONNECT, new Disconnect());
	available_requests.addRequest(REQ_ECHO, new Echo());

	ClientAPI client;
	client.initClient("./config/init.json", available_terminals, available_requests);
	client.connectClient();
	return 0;
}
