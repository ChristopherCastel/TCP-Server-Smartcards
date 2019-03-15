/*
 * client_engine.h
 *
 *  Created on: 26 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Provide all mechanisms (threading, timeouts, socket communication,...) required to implement the API.
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

typedef void (__stdcall *Callback)();

class ClientEngine {
private:
	ConfigWrapper& config = ConfigWrapper::getInstance();
	std::thread requests_thread;
	std::atomic<bool> connected { false };
	std::atomic<bool> initialized { false };
	ITerminalLayer* terminal;
	FlyweightRequests requests;
	Callback notifyConnectionLost;
public:
	ClientEngine(Callback handler) {
		this->notifyConnectionLost = handler;
	}
	virtual ~ClientEngine();

	/**
	 * initClient - initialize the client with the given configuration file.
	 * @param config_path configuration file used to initialize the client.
	 * @param available_terminals the set of available terminal implementations.
	 * @param available_requests the set of available requests.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket initClient(std::string path, FlyweightTerminalFactory available_terminals, FlyweightRequests available_requests);

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

	/**
	 * waitingRequests - wait for requests on the given socket by using the helper function handleRequest.
	 * @param socket the socket from which the client receive data.
	 * @return a ResponsePacket struct containing either the request's response or error codes (under 0) and error descriptions.
	 */
	ResponsePacket waitingRequests(SOCKET socket);

	/**
	 * handleRequest - helper function that performs async actions according to the given request.
	 * The response will be sent back to the given socket.
	 * @param socket the socket to which the response will be sent.
	 * @param request the request to be performed.
	 * @return a ResponsePacket struct containing either the request's response or error codes (under 0) and error descriptions.
	 */
	ResponsePacket handleRequest(SOCKET socket, std::string request);

	/**
	 * setStopFlag - set the flag used to stop (or not) waiting for requests.
	 * @param stop_flag the new value of the stop flag.
	 */
	void setConnectedFlag(bool stop_flag);
};

} /* namespace client */

#endif /* CLIENT_ENGINE_H_ */
