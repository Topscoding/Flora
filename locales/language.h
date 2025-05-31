#pragma once
#include "../include/include.h"

inline string language = "en-us";
inline void set_language_from_computer() {
#ifdef WIN32

#elif __linux__
#elif __APPLE__
#endif
}