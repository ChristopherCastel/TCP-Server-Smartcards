/*
 * flyweight_factory.h
 *
 *  Created on: 28 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Retrieve the right terminal factory at runtime according to the given terminal implementation set in the configuration file.
 *  It is an implementation of the flyweight pattern.
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

	/**
	 * addFactory - add a factory in the cache at the given key.
	 * @param key the key used to store the factory.
	 * @param factory the terminal factory.
	 */
	void addFactory(std::string key, ITerminalFactory* factory);

	/**
	 * getFactory - retrieve to factory at the given key.
	 * @param key the key used to retrieve the factory.
	 * @return the factory at the given key.
	 */
	ITerminalFactory* getFactory(std::string key);
};

} /* namespace terminal */

#endif /* TERMINAL_FLYWEIGHT_FACTORY_H_ */
