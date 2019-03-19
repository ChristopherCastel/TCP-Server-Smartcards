/*
 * error_packet.h
 *
 *  Created on: 25 Feb 2019
 *  Author: STMicroelectronics
 *  Purpose: Provide client and server error code and a struct defining the response format of all function of the application.
 */

#ifndef SRC_RESPONSE_PACKET_H_
#define SRC_RESPONSE_PACKET_H_

#include <string>
#include "nlohmann/json.hpp"
using nlohmann::json;

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

// https://github.com/nlohmann/json#arbitrary-types-conversions
// Used to serialize the ResponsePacket struct in JSON format.
inline void to_json(nlohmann::json& j, const ResponsePacket& e) {
	j = {
		{ "response", e.response },
		{ "err_server_code", e.err_server_code }, { "err_server_description", e.err_server_description },
		{ "err_client_code", e.err_client_code }, { "client_description", e.err_client_description },
		{ "err_terminal_code", e.err_terminal_code }, { "terminal_description", e.err_terminal_description },
		{ "err_card_code", e.err_card_code }, { "err_card_description", e.err_card_description }
	};
}

// https://github.com/nlohmann/json#arbitrary-types-conversions
// Used to convert the json.
inline void from_json(const nlohmann::json& j, ResponsePacket& e) {
	j.at("err_server_code").get_to(e.err_server_code);
	j.at("err_server_description").get_to(e.err_server_description);
	j.at("err_client_code").get_to(e.err_client_code);
	j.at("client_description").get_to(e.err_client_description);
	j.at("err_terminal_code").get_to(e.err_terminal_code);
	j.at("terminal_description").get_to(e.err_terminal_description);
	j.at("err_card_code").get_to(e.err_card_code);
	j.at("err_card_description").get_to(e.err_card_description);
}

} // Namespace client

#endif /* SRC_RESPONSE_PACKET_H_ */
