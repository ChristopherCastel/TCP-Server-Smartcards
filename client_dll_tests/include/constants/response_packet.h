/*
 * error_packet.h
 *
 *  Created on: 25 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Provide client and server error code and a struct defining the response format of all function of the application.
 */

#ifndef SRC_RESPONSE_PACKET_H_
#define SRC_RESPONSE_PACKET_H_

#include <string>

namespace client {

enum ErrorCode {
	SUCCESS = 0, ERR_TIMEOUT = -1, ERR_NETWORK = -2, ERR_CLIENT_CLOSED = -3, ERR_CLIENT_NOT_INITIALIZED = -4
};

/**
 * ResponsePacket struct used as a response of all function calls.
 * By default all error field are set to "SUCCESS" and description to "OK".
 * In case of error, the responsible layer must set the adequate error code and a description.
 * The response field is only valid if there is no negative error code.
 */
struct ResponsePacket {
	std::string response = "OK";

	long int err_server_code = SUCCESS;
	std::string err_server_description = "OK";

	long int err_client_code = SUCCESS;
	std::string err_client_description = "OK";

	long int err_terminal_code = SUCCESS;
	std::string err_terminal_description = "OK";

	long int err_card_code = SUCCESS;
	std::string err_card_description = "OK";
};

} // Namespace client

#endif /* SRC_RESPONSE_PACKET_H_ */
