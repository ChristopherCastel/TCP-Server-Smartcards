/*
 * dll_client_api_wrapper.h
 *
 *  Created on: 08 Mar 2019
 *  Author: STMicroelectronics
 */

#ifdef ADD_EXPORTS
#define ADDAPI __declspec(dllexport)
#else
#define ADDAPI __declspec(dllimport)
#endif

#define ADDCALL __cdecl
#include "client_api.h"
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

client::Callback notifyConnectionLost = 0;

ADDAPI void setCallback(client::Callback handler);
ADDAPI client::ClientAPI* createClientAPI();
ADDAPI void disconnectClient(client::ClientAPI* client, ResponseDLL& response_packet_dll);
ADDAPI void disposeClientAPI(client::ClientAPI* client);
ADDAPI void initClient(client::ClientAPI* client, ResponseDLL& response_packet);
ADDAPI void loadAndListReaders(client::ClientAPI*, ResponseDLL& response_packet);
ADDAPI void connectClient(client::ClientAPI* client, int key, ResponseDLL& response_packet);
void responsePacketForDll(client::ResponsePacket response_packet, ResponseDLL& response_packet_dll);

#ifdef __cplusplus
}
#endif
