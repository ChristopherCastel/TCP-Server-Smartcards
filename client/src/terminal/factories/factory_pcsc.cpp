/*
 * pcsc_factory.cpp
 *
 *  Created on: 28 Feb 2019
 *      Author: Castel Christopher
 */

#include "factory_pcsc.h"
#include "../terminals/terminal_pcsc.h"

namespace client {

ITerminalLayer* PCSCFactory::create() {
	return new TerminalPCSC();
}

} /* namespace client */
