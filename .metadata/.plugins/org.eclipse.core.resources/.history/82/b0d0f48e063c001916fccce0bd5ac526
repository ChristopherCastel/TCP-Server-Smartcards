/*
 * config_wrapper.cpp
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#include <fstream>
#include <iostream>
#include <string>
#include "config_wrapper.h"
#include "nlohmann/json.hpp"

namespace server {

void ConfigWrapper::init(std::string path) {
	std::ifstream i(path);
	i >> config;
}

std::string ConfigWrapper::getValue(std::string key) {
	return config[key];
}

std::string ConfigWrapper::getValue(std::string key, std::string default_value) {
	return config[key].is_null() ? default_value : config[key].get<std::string>();
}

} /* namespace client */
