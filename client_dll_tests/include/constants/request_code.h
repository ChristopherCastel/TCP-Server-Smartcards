/*
 * request_code.h
 *
 *  Created on: 22 Feb 2019
 *  Author: STMicroelectronics
 *  Purpose: Provide available request's code and a way to convert them to a string description.
 */

#ifndef SRC_REQUEST_CODE_H_
#define SRC_REQUEST_CODE_H_

#include <string>

namespace client {

enum RequestCode {
	REQ_CONNECT = 0, REQ_DIAG, REQ_DISCONNECT, REQ_ECHO, REQ_INIT, REQ_RESTART, REQ_COMMAND
};

/**
 * requestCodeToString - convert an enum value to the matching string description.
 * @param r the request code to be converted.
 * @return the matching string description.
 */
inline const std::string requestCodeToString(RequestCode r) {
	switch (r) {
	case REQ_CONNECT:
		return "REQ_CONNECT";
	case REQ_DIAG:
		return "REQ_DIAG";
	case REQ_DISCONNECT:
		return "REQ_DISCONNECT";
	case REQ_ECHO:
		return "REQ_ECHO";
	case REQ_INIT:
		return "REQ_INIT";
	case REQ_RESTART:
		return "REQ_RESTART";
	case REQ_COMMAND:
		return "REQ_COMMAND";
	default:
		return "[Unknown Request Code]";
	}
}

} /* namespace client */

#endif /* SRC_REQUEST_CODE_H_ */
