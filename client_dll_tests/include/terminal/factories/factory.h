/*
 * terminal_factory.h
 *
 *  Created on: 28 Feb 2019
 *  Author: STMicroelectronics
 *  Purpose: Interface for implementing the factories.
 *  It is an implementation of the factory pattern.
 */

#ifndef TERMINAL_BASE_TERMINAL_FACTORY_H_
#define TERMINAL_BASE_TERMINAL_FACTORY_H_

#include "../terminals/terminal.h"

namespace client {

class ITerminalFactory {
public:
	ITerminalFactory() {};
	virtual ~ITerminalFactory() {};

	/**
	 * create - instantiate a terminal.
	 * @return an instance of ITerminalLayer.
	 */
	virtual ITerminalLayer* create() = 0;
};

} /* namespace client */

#endif /* TERMINAL_BASE_TERMINAL_FACTORY_H_ */
