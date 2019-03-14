/*
 * main.cpp
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#include "server/server_api.h"
#include <iostream>

using namespace server;

int __cdecl main(void) {
	ServerAPI server;
	server.initServer("./config/init.json");
	server.startServer();
	Sleep(10000);
	server.diagClient(1);
	server.echoClient(1);
	server.sendCommand(1, "00 A4 04 00 00");
	server.stopServer();
	return 0;
}
