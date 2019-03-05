/*
 * main.cpp
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#include "server/server_api.h"
using namespace server;

int __cdecl main(void) {
	ServerAPI server;
	server.initServer("./config/init.json");
	server.startServer();
	Sleep(6000);
	server.diagClient(1);
	server.echoClient(1);
	Sleep(1500);
	server.stopServer();
	return 0;
}
