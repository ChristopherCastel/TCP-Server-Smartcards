/*
 * flyweight_factory.h
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#ifndef TERMINAL_FLYWEIGHT_FACTORY_H_
#define TERMINAL_FLYWEIGHT_FACTORY_H_

#include <map>

#include "factories/factory.h"
#include "factories/factory_pcsc.h"

namespace client {

class FlyweightTerminalFactory {
private:
	std::map<std::string, ITerminalFactory*> factories;
public:
	FlyweightTerminalFactory() {};

	virtual ~FlyweightTerminalFactory() {};

	void addFactory(std::string key, ITerminalFactory* factory);

	ITerminalFactory* getFactory(std::string key);
};

} /* namespace terminal */

#endif /* TERMINAL_FLYWEIGHT_FACTORY_H_ */
