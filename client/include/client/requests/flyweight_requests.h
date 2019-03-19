/*
 * flyweight_requests.h
 *
 *  Created on: 01 Mar 2019
 *      Author: STMicroelectronics
 */

#ifndef SRC_CLIENT_REQUESTS_FLYWEIGHT_REQUESTS_H_
#define SRC_CLIENT_REQUESTS_FLYWEIGHT_REQUESTS_H_

#include <map>
#include "request.h"
#include "../../constants/request_code.h"

namespace client {

class FlyweightRequests {
private:
	std::map<RequestCode, IRequest*> requests;
public:
	FlyweightRequests() {};

	virtual ~FlyweightRequests() {};

	void addRequest(RequestCode key, IRequest* request);

	IRequest* getRequest(RequestCode key);
};

} /* namespace client */

#endif /* SRC_CLIENT_REQUESTS_FLYWEIGHT_REQUESTS_H_ */
