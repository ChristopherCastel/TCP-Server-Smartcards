/*
 * ClientData.cpp
 *
 *  Created on: 20 Feb 2019
 *      Author: Castel Christopher
 */

#include "server/client_data.h"

namespace server {

ClientData::ClientData(SOCKET socket, int id, std::string name) {
	this->socket = socket;
	this->id = id;
	this->name = name;
}

int ClientData::getId() {
	return id;
}

std::string ClientData::getName() {
	return name;
}

SOCKET ClientData::getSocket() {
	return socket;
}

void ClientData::setId(int id) {
	this->id = id;
}

void ClientData::setName(std::string name) {
	this->name = name;
}

void ClientData::setSocket(SOCKET socket) {
	this->socket = socket;
}

} /* namespace server */
