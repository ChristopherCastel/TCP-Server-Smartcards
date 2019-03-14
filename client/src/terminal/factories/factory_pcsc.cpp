/*
 * pcsc_factory.cpp
 *
 *  Created on: 28 Feb 2019
 *  Author: Castel Christopher
 */

#include "terminal/factories/factory_pcsc.h"
#include "terminal/terminals/terminal_pcsc.h"

namespace client {

ITerminalLayer* PCSCFactory::create() {
	return new TerminalPCSC();
}

} /* namespace client */
