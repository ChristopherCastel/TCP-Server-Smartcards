/*
 * main.cpp
 *
 *  Created on: 08 Mar 2019
 *   Author: Castel Christopher
 */

#include <stdio.h>
#include <iostream>
#include "client/dll_client_api_wrapper.h"
#include "client/client_api.h"

using namespace client;

int main(int argc, char** argv) {
	ClientAPI* client = createClientAPI();
	ResponseDLL resp;
	initClient(client, resp);
	loadAndListReaders(client, resp);
	connectClient(client, 0, resp);
	disconnectClient(client, resp);
	return 0;
}
