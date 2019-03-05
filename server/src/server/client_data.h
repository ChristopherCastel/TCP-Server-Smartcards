/*
 * ClientData.h
 *
 *  Created on: 20 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef CLIENT_DATA_H_
#define CLIENT_DATA_H_

#include <string>
#include <winsock2.h>

namespace server {

class ClientData {
private:
	// The socket the client is using.
	SOCKET socket = INVALID_SOCKET;
	// Unique ID of this client. The ID is until within program execution.
	int id;
	// Custom name of the client. Not required to be unique but it is advised for visibility.
	std::string name = "no name";
protected:
public:
	ClientData() {}

	ClientData(SOCKET socket, int id, std::string name);

	virtual ~ClientData() {}

	int getId();

	std::string getName();

	SOCKET getSocket();

	void setId(int id);

	void setName(std::string name);

	void setSocket(SOCKET socket);
};

} /* namespace server */

#endif /* CLIENT_DATA_H_ */
