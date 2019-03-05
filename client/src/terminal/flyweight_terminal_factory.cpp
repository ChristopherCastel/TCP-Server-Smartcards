/*
 * flyweight_factory.cpp
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#include <map>

#include "flyweight_terminal_factory.h"
#include "terminals/terminal.h"

namespace client {

void FlyweightTerminalFactory::addFactory(std::string key, ITerminalFactory* factory) {
	factories.insert(std::make_pair(key, factory));
}

ITerminalFactory* FlyweightTerminalFactory::getFactory(std::string key) {
	return factories.at(key);
}

} /* namespace terminal */
