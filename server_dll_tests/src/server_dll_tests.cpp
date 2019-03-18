#include <stdio.h>
#include <iostream>
#include "server/dll_server_api_wrapper.h"
#include "server/server_api.h"

using namespace server;

int main() {
	ServerAPI* server = createServerAPI();
	ResponseDLL resp;
	initServer(server, resp);
	printf("%s\n", resp.response);
	printf("%d\n", resp.err_server_code);
	printf("%s\n", resp.err_server_description);
	printf("%d\n", resp.err_client_code);
	printf("%s\n", resp.err_client_description);
	printf("%d\n", resp.err_terminal_code);
	printf("%s\n", resp.err_terminal_description);
	printf("%d\n", resp.err_card_code);
	printf("%s\n", resp.err_card_description);

	startServer(server, resp);
	return 0;
}
