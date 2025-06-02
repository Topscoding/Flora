#pragma once
#include "../include/include.h"
#include "../include/define.h"
class spliter {
// private
	static bool is_same_type(const char &a, const char &b) {
		if (a == '(' || a == ')' || b == '(' || b == ')' ||
			a == '[' || a == ']' || b == '[' || b == ']' ||
			a == '{' || a == '}' || b == '{' || b == '}')
			return false;
		if ((isdigit(a) && isdigit(b)) ||
			(isalpha(a) && isalpha(b)))
			return true;
		if (isalnum(a) || isalnum(b))
			return false;
		return true;
	}
public:
	static vector <string> split_line_into_words(const string &str) {
		vector <string> result;
		string t;
		for (const auto &ch : str) {
			if (isspace(ch)) {
				if (!t.empty()) {
					result.emplace_back(t);
					t.clear();
				}
			} else {
				if (t.empty())
					t.push_back(ch);
				else
					if (!is_same_type(ch, t.back()))
						result.emplace_back(t);
			}
		}
		return result;
	}
};