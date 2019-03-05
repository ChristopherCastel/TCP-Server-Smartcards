/*
 * config_wrapper.h
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef SRC_CONFIG_WRAPPER_H_
#define SRC_CONFIG_WRAPPER_H_

#include <string>
#include "nlohmann/json.hpp"

namespace server {

// singleton
class ConfigWrapper { // https://stackoverflow.com/a/1008289
public:
	static ConfigWrapper& getInstance() {
		static ConfigWrapper instance;
		return instance;
	}

	void init(std::string path);

	std::string getValue(std::string key);

	std::string getValue(std::string key, std::string default_value);

	int getValue(std::string key, int default_value);
private:
	ConfigWrapper() {}
	nlohmann::json config;
public:
	ConfigWrapper(ConfigWrapper const&) = delete;

	void operator=(ConfigWrapper const&) = delete;
};

} /* namespace client */

#endif /* SRC_CONFIG_WRAPPER_H_ */

