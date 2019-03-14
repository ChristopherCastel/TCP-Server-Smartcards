/*
 * ClientData.h
 *
 *  Created on: 20 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Provide a class wrapping the client's data.
 */

#ifndef CLIENT_DATA_H_
#define CLIENT_DATA_H_

#include <string>
#include <winsock2.h>

namespace server {

class ClientData {
private:
	int id;
	SOCKET socket = INVALID_SOCKET;
	std::string name = "no name";
protected:
public:
	ClientData() {}
	ClientData(SOCKET socket, int id, std::string name);
	virtual ~ClientData() {}

	/**
	 * getId - return the integer value of the field "id".
	 * @return the client's id.
	 */
	int getId();

	/**
	 * getName - return the string value of the field "name".
	 * @return the client's name.
	 */
	std::string getName();

	/**
	 * getSocket - return the socket between the client and the server.
	 * @return the client's socket.
	 */
	SOCKET getSocket();

	/**
	 * setId - set client's id.
	 * The given id must be unique and stay unique.
	 * @param id the id to be set.
	 */
	void setId(int id);

	/**
	 * setName - set the client's name.
	 * @param name the name to be set.
	 */
	void setName(std::string name);

	/**
	 * setSocket - set the client's socket.
	 * @param socket the socket to be set.
	 */
	void setSocket(SOCKET socket);
};

} /* namespace server */

#endif /* CLIENT_DATA_H_ */
