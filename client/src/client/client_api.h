/*
 * client_api.h
 *
 *  Created on: 26 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef CLIENT_API_H_
#define CLIENT_API_H_

#include "client_engine.h"
#include "requests/flyweight_requests.h"
#include "../constants/response_packet.h"
#include "../terminal/flyweight_terminal_factory.h"

namespace client {

class ClientAPI {
private:
	ClientEngine engine;
protected:
public:
	ClientAPI() {}

	virtual ~ClientAPI() {}

	ResponsePacket initClient(std::string config_path, FlyweightTerminalFactory available_terminals, FlyweightRequests available_requests);

	ResponsePacket connectClient();

	ResponsePacket disconnectClient();
};

} /* namespace client */

#endif /* CLIENT_API_H_ */
