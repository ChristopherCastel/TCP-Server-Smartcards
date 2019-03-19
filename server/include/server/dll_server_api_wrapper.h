/*
 * dll_client_api_wrapper.h
 *
 *  Created on: 08 Mar 2019
 *      Author: STMicroelectronics
 */

#ifdef ADD_EXPORTS
#define ADDAPI __declspec(dllexport)
#else
#define ADDAPI __declspec(dllimport)
#endif

#define ADDCALL __cdecl
#include "server/server_api.h"
#include "constants/response_packet.h"

struct ResponseDLL {
	char response[2048];
	long int err_server_code;
	char err_server_description[2048];
	long int err_client_code;
	char err_client_description[2048];
	long int err_terminal_code;
	char err_terminal_description[2048];
	long int err_card_code;
	char err_card_description[2048];
};

#ifdef __cplusplus
extern "C" {
#endif

ADDAPI server::ServerAPI* createServerAPI();
ADDAPI void initServer(server::ServerAPI* server, ResponseDLL& response_packet);
ADDAPI void startServer(server::ServerAPI* server, ResponseDLL& response_packet);
ADDAPI void listClients(server::ServerAPI* server, ResponseDLL& response_packet);
ADDAPI void echoClient(server::ServerAPI* server, int id_client, ResponseDLL& response_packet);
ADDAPI void diagClient(server::ServerAPI* server, int id_client, ResponseDLL& response_packet);
ADDAPI void sendCommand(server::ServerAPI* server, int id_client, char* command, ResponseDLL& response_packet);
ADDAPI void restartTarget(server::ServerAPI* server, int id_client, ResponseDLL& response_packet);
ADDAPI void stopClient(server::ServerAPI* server, int id_client, ResponseDLL& response_packet);
ADDAPI void stopServer(server::ServerAPI* server, ResponseDLL& response_packet);
ADDAPI void disposeServerAPI(server::ServerAPI* server);
void responsePacketForDll(server::ResponsePacket response_packet, ResponseDLL& response_packet_dll);

#ifdef __cplusplus
}
#endif
