/*
 * server.h
 *
 *  Created on: 13 Feb 2019
 *  Author: STMicroelectronics
 *  Purpose: Provide an API for interacting with the server and its clients.
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "client_data.h"
#include "server_engine.h"
#include "constants/request_code.h"

namespace server {

typedef void (__stdcall *Callback)(int id_client, const char* name_client);

class ServerAPI {
private:
	ServerEngine* engine;
protected:
public:
	ServerAPI(Callback notifyConnectionAccepted) {
		this->engine = new ServerEngine(notifyConnectionAccepted);
	}

	virtual ~ServerAPI() {}

	/**
	 * initServer - initialize the server with the given configuration file.
	 * @param path configuration file used to initialize the server.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket initServer(std::string path);

	/**
	 * startServer - start the server. The server is now able to listen to accept connections and to process incoming requests.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket startServer();

	/*
	 * listclients - returns a ResponsePacket containing data in the "response" field.
	 * The "response" field contains the number of connected clients, their id and their name.
	 * The "response" field will be formatted this way: ClientsNumber|ClientID|ClientName|...|...
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket listClients();

	/**
	 * echoClient - return a ResponsePacket used to check that the client is working without error.
	 * The ResponsePacket struct contains no data in the "response" field.
	 * No errorvalue under 0 in the ResponsePacket struct means the client is working.
	 * @param id_client
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket echoClient(int id_client);

	/**
	 * diagClient - return details about the client and its underlying layers.
	 * The details will be in the field "response" of the ResponsePacket structure.
	 * The details will be formatted this way: TheReaderName|TheReaderStatus|TheReaderProtocolUsed
	 * @param id_client
	 * @return a ResponsePacket struct containing either the data or error codes and error descriptions.
	 */
	ResponsePacket diagClient(int id_client);

	/**
	 * sendCommand - return a ResponsePacket struct containing the target's response in the "response" field.
	 * @param id_client
	 * @param command the command that will be send to the given target.
	 * @return a ResponsePacket struct containing either the target's response or error codes (value under 0) and error descriptions in case of error.
	 */
	ResponsePacket sendCommand(int id_client, std::string command);

	/**
	 * restartTarget - restart the given target.
	 * @param id_client the target to be restarted.
	 * @return a ResponsePacket struct containing possible error codes (under 0) and error descriptions.
	 */
	ResponsePacket restartTarget(int id_client);

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
	ResponsePacket stopServer();
};

}  // namespace server

#endif /* SERVER_H_ */
