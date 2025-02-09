/*
 Copyright 2017 GlobalPlatform, Inc.

 Licensed under the GlobalPlatform/Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

https://github.com/GlobalPlatform/SE-test-IP-connector/blob/master/Charter%20and%20Rules%20for%20the%20SE%20IP%20connector.docx

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include <fstream>
#include <iostream>
#include <string>
#include "config/config_wrapper.h"
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
