/*
 * config_wrapper.h
 *
 *  Created on: 28 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Wrapper for the configuration file.
 */

#ifndef SRC_CONFIG_WRAPPER_H_
#define SRC_CONFIG_WRAPPER_H_

#include <string>
#include "nlohmann/json.hpp"

namespace server {

// singleton pattern
class ConfigWrapper { // https://stackoverflow.com/a/1008289
public:
	static ConfigWrapper& getInstance() {
		static ConfigWrapper instance;
		return instance;
	}

	/**
	 * init - retrieve the json from the given configuration file.
	 * @param path the configuration file.
	 */
	void init(std::string path);

	/**
	 * getValue - retrieve the value at the given key.
	 * @param key the key where the data is meant to be.
	 * @return the retrieved value.
	 */
	std::string getValue(std::string key);

	/**
	 * getValue - retrieve the value at the given key or the default value if the key don't exist.
	 * @param key the key where the data is meant to be.
	 * @param default_value the return value if the key is not found.
	 * @return the retrieved value or the given default value.
	 */
	std::string getValue(std::string key, std::string default_value);
private:
	ConfigWrapper() {}
	nlohmann::json config;
public:
	ConfigWrapper(ConfigWrapper const&) = delete;
	void operator=(ConfigWrapper const&) = delete;
};

} /* namespace client */

#endif /* SRC_CONFIG_WRAPPER_H_ */
