/*
 * client_engine.h
 *
 *  Created on: 26 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef CLIENT_ENGINE_H_
#define CLIENT_ENGINE_H_

#include <atomic>
#include <thread>
#include <ws2tcpip.h>

#include "requests/flyweight_requests.h"
#include "../config/config_wrapper.h"
#include "../constants/response_packet.h"
#include "../terminal/flyweight_terminal_factory.h"
#include "../terminal/terminals/terminal.h"

namespace client {

class ClientEngine {
private:
	ConfigWrapper& config = ConfigWrapper::getInstance();
	std::thread requests_thread;
	std::atomic<bool> stop_flag { false };
	bool initialized = false;
	ITerminalLayer* terminal;
	FlyweightRequests requests;
public:
	ClientEngine() {}

	virtual ~ClientEngine();

	ResponsePacket mock();

	ResponsePacket connectClient();

	ResponsePacket disconnectClient();

	ResponsePacket handleRequest(SOCKET socket, std::string request);

	ResponsePacket initClient(std::string path, FlyweightTerminalFactory available_terminals, FlyweightRequests available_requests);

	ResponsePacket waitingRequests(SOCKET socket);

	void setStopFlag(bool stop_flag);
};

} /* namespace client */

#endif /* CLIENT_ENGINE_H_ */
