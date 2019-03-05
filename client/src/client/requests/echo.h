/*
 * echo.h
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#ifndef SRC_CLIENT_REQUESTS_ECHO_H_
#define SRC_CLIENT_REQUESTS_ECHO_H_

#include "request.h"
#include "../../terminal/terminals/terminal.h"

namespace client {
class ClientEngine;

class Echo : public IRequest {
public:
	Echo() {}
	~Echo() {}
	ResponsePacket run(ITerminalLayer* terminal, ClientEngine* client_engine);
};

} /* namespace client */

#endif /* SRC_CLIENT_REQUESTS_ECHO_H_ */
