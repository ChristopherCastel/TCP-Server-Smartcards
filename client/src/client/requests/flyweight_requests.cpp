/*
 * flyweight_requests.cpp
 *
 *  Created on: 01 Mar 2019
 *      Author: Castel Christopher
 */

#include <map>
#include "client/requests/flyweight_requests.h"
#include "client/requests/request.h"

namespace client {

void FlyweightRequests::addRequest(RequestCode key, IRequest* factory) {
	requests.insert(std::make_pair(key, factory));
}

IRequest* FlyweightRequests::getRequest(RequestCode key) {
	return requests.at(key);
}

} /* namespace client */
