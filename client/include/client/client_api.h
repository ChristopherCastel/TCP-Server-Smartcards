/*
 * client_api.h
 *
 *  Created on: 26 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Provide an API for interacting with the client.
 */

#ifndef CLIENT_API_H_
#define CLIENT_API_H_

#include "client_engine.h"
#include "requests/flyweight_requests.h"
#include "../constants/response_packet.h"
#include "../terminal/flyweight_terminal_factory.h"

namespace client {

typedef void (__stdcall *Callback)();

class ClientAPI {
private:
	ClientEngine* engine;
protected:
public:
	ClientAPI(Callback handler) {
		this->engine = new ClientEngine(handler);
	}

	virtual ~ClientAPI();

	/**
	 * initClient - initialize the client with the given configuration file.
	 * @param config_path configuration file used to initialize the client.
	 * @param available_terminals the set of available terminal implementations.
	 * @param available_requests the set of available requests.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket initClient(std::string config_path, FlyweightTerminalFactory available_terminals, FlyweightRequests available_requests);

	/**
	 * loadAndListReaders - load and list available readers.
	 * The "response" field contains the id and name of each reader.
	 * The "response" field will be formatted this way: ReaderID|ReaderName|...|...
	 * @return a ResponsePacket struct containing either the list of readers or error codes (under 0) and error descriptions.
	 */
	ResponsePacket loadAndListReaders();

	/**
	 * connectClient - connect to the given reader and to the server.
	 * @param terminal_key the key corresponding to a reader.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket connectClient(int terminal_key);

	/**
	 * disconnectClient - disconnect the cliet from the server and disconnect the terminal.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket disconnectClient();
};

} /* namespace client */

#endif /* CLIENT_API_H_ */
