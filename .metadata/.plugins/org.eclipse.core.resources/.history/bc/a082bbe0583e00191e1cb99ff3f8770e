/*
 * diag.h
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#ifndef SRC_CLIENT_REQUESTS_DIAG_H_
#define SRC_CLIENT_REQUESTS_DIAG_H_

#include "request.h"

namespace client {
class ClientEngine;

class Diag : public IRequest {
public:
	Diag() {}
	~Diag() {}
	ResponsePacket run(ITerminalLayer* terminal, ClientEngine* client_engine);
};

} /* namespace client */

#endif /* SRC_CLIENT_REQUESTS_DIAG_H_ */
