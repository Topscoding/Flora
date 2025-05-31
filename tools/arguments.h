#pragma once
#include "../include/include.h"
#include "../locales/error.h"
#include "../locales/info.h"
inline void argument(const string &message) {
	if (message == "version") {
		info(VERSION);
	} else if (message == "help") {
		info(HELP);
	} else {
		error(ARGUMENT_VALUE_ERROR, {".", message, "version", "help"});
	}
}