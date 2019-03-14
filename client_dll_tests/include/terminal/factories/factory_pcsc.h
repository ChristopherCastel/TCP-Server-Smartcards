/*
 * pcsc_factory.h
 *
 *  Created on: 28 Feb 2019
 *  Author: Castel Christopher
 *  Purpose: Subclass of ITerminalFactory for PCSC implementation.
 */

#ifndef TERMINAL_PCSC_FACTORY_H_
#define TERMINAL_PCSC_FACTORY_H_

#include "factory.h"

namespace client {

class PCSCFactory : public ITerminalFactory {
public:
	PCSCFactory() {};
	~PCSCFactory() {};
	ITerminalLayer* create();
};

} /* namespace client */

#endif /* TERMINAL_PCSC_FACTORY_H_ */
