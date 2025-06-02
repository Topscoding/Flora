#pragma once
#include "../include/include.h"
#include "language.h"
#define INFO_VERSION 0
#define INFO_HELP 1
inline void info(const int &type) {
	if (type == INFO_VERSION) {
		if (language == "en-us") {
			cout << "Flora programming language 0.0.1 version" << endl;
			cout << "Input .help to view docs." << endl;
		} else if (language == "zh-cn") {
			cout << "Flora 编程语言版本 0.0.1" << endl;
			cout << "输入 .help 查看文档." << endl;
		}
	} else if (type == INFO_HELP) {
		if (language == "en-us") {
			cout << "Usage: ./flora [--option] or ./flora then input .option" << endl;
			cout << "Options:" << endl;
			cout << " - version: View the program's version" << endl;
			cout << " - help: View this help" << endl;
			cout << "Usage: ./flora name.flora" << endl;
			cout << "    or ./flora then input statements" << endl;
		} else if (language == "zh-cn") {
			cout << "未完善" << endl;
		}
	}
}