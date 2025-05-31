#pragma once
#include "../include/include.h"
#include "../include/define.h"
class spliter {
// private
	static bool is_same_type(const char &a, const char &b) {
		if (a == '(' || a == ')' || b == '(' || b == ')' ||
			a == '[' || a == ']' || b == '[' || b == ']' ||
			a == '{' || a == '}' || b == '{' || b == '}') {
			return false;
		}
		if ((isdigit(a) && isdigit(b)) ||
			(isalpha(a) && isalpha(b))) {
			return true;
		}
		
	}
public:
	static vector <string> split_line_into_words(const string &str) {
		vector <string> result;

		return result;
	}
};