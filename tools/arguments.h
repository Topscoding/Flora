#pragma once
#include "../include/include.h"
#include "../locales/error.h"
#include "../locales/info.h"
inline void argument(const string &message) {
	if (message == "version") {
		info(INFO_VERSION);
	} else if (message == "help") {
		info(INFO_HELP);
	} else {
		error(ERROR_ARGUMENT_VALUE_ERROR, {".", message, "version", "help"});
	}
}