/*
 * engine.h
 *
 *  Created on: 22 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef SRC_SERVER_ENGINE_H_
#define SRC_SERVER_ENGINE_H_

#include <atomic>
#include <map>
#include <thread>
#include <winsock2.h>

#include "client_data.h"
#include "../config/config_wrapper.h"
#include "../constants/request_code.h"
#include "../constants/response_packet.h"

using namespace responses;

namespace server {

class ServerEngine {
private:
	ConfigWrapper& config = ConfigWrapper::getInstance();
	std::thread connection_thread;
	std::atomic<bool> stop_flag { false };
	std::map<int, ClientData*> clients;
	SOCKET listen_socket = INVALID_SOCKET;
	int next_client_id = 0;
protected:
public:
	ServerEngine() {}

	virtual ~ServerEngine() {}

	ResponsePacket asyncRequest(SOCKET client_socket, std::string to_send, DWORD timeout);

	ResponsePacket cleanupSocket(SOCKET socket);

	ResponsePacket connectionHandshake(SOCKET client_socket);

	ResponsePacket handleConnections(SOCKET listen_socket);

	ResponsePacket handleRequest(int id_client, RequestCode request, std::string data = "", DWORD timeout = 2000);

	ResponsePacket initServer(std::string path);

	ResponsePacket listClients();

	ResponsePacket startListening();

	ResponsePacket stopClient(int id_client);

	ResponsePacket stopAllClients();
};

} /* namespace server */

#endif /* SRC_SERVER_ENGINE_H_ */
