#pragma once
#include "../include/define.h"
#include "../include/include.h"
#include "../locales/error.h"
inline unordered_map <string, any> variables;
inline void new_variable(const string &name, const any &value, debug_info) {
	if (variables.contains(name)) {
		error(ERROR_VARIABLE_ALREADY_EXISTS, {name}, debug_msg);
		return ;
	}
	variables[name] = value;
}
inline void set_variable(const string &name, const any &value) {
	variables[name] = value;
}
inline pair <any, bool> get_variable(const string &name, debug_info) {
	if (variables.contains(name)) {
		return make_pair(variables[name], false);
	}
	error(ERROR_VARIABLE_NOT_EXISTS, {name}, debug_msg);
	return make_pair(nullptr, true);
}
