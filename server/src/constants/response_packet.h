/*
 * error_packet.h
 *
 *  Created on: 25 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef SRC_RESPONSE_PACKET_H_
#define SRC_RESPONSE_PACKET_H_

#include <string>
#include "nlohmann/json.hpp"
using nlohmann::json;

namespace responses {

enum ErrorCode {
	SUCCESS = 0, ERR_TIMEOUT = -1, ERR_NETWORK = -2, ERR_CLIENT_CLOSED = -3
};

struct ResponsePacket {
	std::string response = "OK";

	ErrorCode err_server_code = SUCCESS;
	std::string err_server_description = "OK";

	ErrorCode err_client_code = SUCCESS;
	std::string client_description = "OK";

	ErrorCode err_terminal_code = SUCCESS;
	std::string terminal_description = "OK";

	ErrorCode err_card_code = SUCCESS;
	std::string err_card_description = "OK";
};

// https://github.com/nlohmann/json#arbitrary-types-conversions
// used to serialize the struct in JSON
inline void to_json(nlohmann::json& j, const ResponsePacket& e) {
	j = {
		{ "response", e.response },
		{ "err_server_code", e.err_server_code }, { "err_server_description", e.err_server_description },
		{ "err_client_code", e.err_client_code }, { "client_description", e.client_description },
		{ "err_terminal_code", e.err_terminal_code }, { "terminal_description", e.terminal_description },
		{ "err_card_code", e.err_card_code }, { "err_card_description", e.err_card_description }
	};
}

// used to convert the json
inline void from_json(const nlohmann::json& j, ResponsePacket& e) {
	j.at("err_server_code").get_to(e.err_server_code);
	j.at("err_server_description").get_to(e.err_server_description);
	j.at("err_client_code").get_to(e.err_client_code);
	j.at("client_description").get_to(e.client_description);
	j.at("err_terminal_code").get_to(e.err_terminal_code);
	j.at("terminal_description").get_to(e.terminal_description);
	j.at("err_card_code").get_to(e.err_card_code);
	j.at("err_card_description").get_to(e.err_card_description);
}

} // Namespace responses

#endif /* SRC_RESPONSE_PACKET_H_ */
