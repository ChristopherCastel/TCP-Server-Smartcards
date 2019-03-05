/*
 * server.h
 *
 *  Created on: 13 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "client_data.h"
#include "server_engine.h"
#include "../constants/request_code.h"

namespace server {

class ServerAPI {
private:
	ServerEngine engine;
protected:
public:
	ServerAPI() {}

	virtual ~ServerAPI() {}

	ResponsePacket diagClient(int id_client);

	ResponsePacket echoClient(int id_client);

	ResponsePacket initServer(std::string path);

	ResponsePacket listClients();

	ResponsePacket restartTarget(int id_client);

	ResponsePacket startServer();

	ResponsePacket sendCommand(int id_client, std::string command);

	ResponsePacket stopClient(int id_client);

	ResponsePacket stopServer();
};

}  // namespace server

#endif /* SERVER_H_ */
