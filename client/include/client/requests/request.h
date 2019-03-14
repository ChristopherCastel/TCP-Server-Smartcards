/*
 * request.h
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#ifndef SRC_CLIENT_REQUESTS_REQUEST_H_
#define SRC_CLIENT_REQUESTS_REQUEST_H_

#include "../../constants/response_packet.h"
#include "../../terminal/terminals/terminal.h"

namespace client {

class ClientEngine;
class IRequest {
public:
	IRequest() {}
	virtual ~IRequest() {}
	virtual ResponsePacket run(ITerminalLayer* terminal, ClientEngine* client_engine, char unsigned command[], DWORD command_length) = 0;
};

} /* namespace client */

#endif /* SRC_CLIENT_REQUESTS_REQUEST_H_ */
