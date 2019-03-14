/*
 * disconnect.h
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#ifndef SRC_CLIENT_REQUESTS_DISCONNECT_H_
#define SRC_CLIENT_REQUESTS_DISCONNECT_H_

#include "request.h"
#include "../../terminal/terminals/terminal.h"

namespace client {
class ClientEngine;

class Disconnect : public IRequest {
public:
	Disconnect() {}
	~Disconnect() {}
	ResponsePacket run(ITerminalLayer* terminal, ClientEngine* client_engine, char unsigned command[], DWORD command_length);
};

} /* namespace client */

#endif /* SRC_CLIENT_REQUESTS_DISCONNECT_H_ */
