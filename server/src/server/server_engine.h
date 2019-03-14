/*
 * engine.h
 *
 *  Created on: 22 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Provide all mechanisms (threading, timeouts, socket communication,...) required to implement the API.
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

	/**
	 * initServer - init the logger and the configuration values.
	 * @param path the configuration file to read.
 	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket initServer(std::string path);

	/**
	 * startListening - setup the socket and start listening to incoming connections on the ip and port given during the initialization.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket startListening();

	/**
	 * handleConnections - handle connections request and use helper function "connectionHandshake" at each connection request.
	 * @param listen_socket the socket used to listen for connections.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket handleConnections(SOCKET listen_socket);

	/**
	 * connectionHandshake - helper function used to handle a connection asynchronously.
	 * The handshake ensures that the client send its data (such as its name) after requesting for a connection.
	 * @param client_socket the socket where the handshake is performed.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket connectionHandshake(SOCKET client_socket);

	/**
	 * handleRequest - create a json formatted string with the given parameters and send it the given client with the help of the function "asyncRequest".
	 * @param id_client the client's id to send request to.
	 * @param request the request to be performed, such as "diag", "echo",...
	 * @param date the request's data, such as "04 04 00 00".
	 * @param timeout the timeout used to elapse the request.
	 * @return a ResponsePacket struct containing the request's result.
	 */
	ResponsePacket handleRequest(int id_client, RequestCode request, std::string data = "", DWORD timeout = 2000);

	/**
	 * asyncRequest - helper function to send asynchronously the given data on the given socket.
	 * The request elapses is no response is received after the given timeout.
	 * @param client_socket the socket to send data on.
	 * @param to_send the actual data to be sent.
	 * @param timeout the timeout in ms used to unblock the request.
	 * @return a ResponsePacket struct containing the request's result.
	 */
	ResponsePacket asyncRequest(SOCKET client_socket, std::string to_send, DWORD timeout);

	/*
	 * listClients - returns a ResponsePacket containing all clients' data in the "response" field.
	 * The "response" field contains the number of connected clients, their id and their name.
	 * The "response" field will be formated in this way: ClientsNumber|ClientID|ClientName|...|...
	 * @return a ResponsePacket struct containing either clients' data or error codes (under 0) and error descriptions.
	 */
	ResponsePacket listClients();

	/**
	 * stopClient - stop the given client and all its underlying layers.
	 * @param id_client the client to stop.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket stopClient(int id_client);

	/**
	 * stopServer - stop the server and all its clients and their underlying layers.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket stopAllClients();
};

} /* namespace server */

#endif /* SRC_SERVER_ENGINE_H_ */
