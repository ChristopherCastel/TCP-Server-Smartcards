/*
 * command.h
 *
 *  Created on: 01 Mar 2019
 *  Author: STMicroelectronics
 */

#ifndef SRC_CLIENT_REQUESTS_COMMAND_H_
#define SRC_CLIENT_REQUESTS_COMMAND_H_

#include "request.h"
#include "../../terminal/terminals/terminal.h"

namespace client {
class ClientEngine;

class Command : public IRequest {
public:
	Command() {}
	~Command() {}
	ResponsePacket run(ITerminalLayer* terminal, ClientEngine* client_engine, char unsigned command[], DWORD command_length);
};

} /* namespace client */

#endif /* SRC_CLIENT_REQUESTS_COMMAND_H_ */
