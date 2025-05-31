#pragma once
#include "language.h"
#include "../include/include.h"
#include "../include/define.h"
#define FILE_OPEN_ERROR 0
#define STDIN_READ_ERROR 1
#define ARGUMENT_VALUE_ERROR 2
#define ARGUMENT_TYPE_ERROR 3
#define VARIABLE_ALREADY_EXISTS 4
#define VARIABLE_NOT_EXISTS 5
inline void panic() {
	cout << "Error! The program went some error." << endl;
	cout << "If you see this, it means you did something unexceptional." << endl;
	cout << "Please make sure you haven't edit the source code uncorrected." << endl;
	cout << "Another way, this is a tool to debug the language, to make sure the developers haven't wrote error code." << endl;
	exit(-1);
}
inline void error(const int &message, const vector <string> &args, const string &function_name = "", const int &line = -1, const int &column = -1) {
	if (!function_name.empty() && line != -1 && column != -1) {
		if (language == "en-us") {
			cout << format("In function {}, line {}, column {}: ", function_name, line, column) << endl;
		} else if (language == "zh-cn") {
			cout << format("在函数 {} 中第 {} 行第 {} 列: ",  function_name, line, column) << endl;
		}
	}
	if (message == FILE_OPEN_ERROR) {
		/*
		 * args[0] file path
		 * args[1 ~ end] error message
		 */
		if (args.size() != 2) {
			panic();
		}
		if (language == "en-us") {
			cout << format("Error when open file {}. ", args[0]) << endl;
			cout << format("Error message: {}", args[1]) << endl;
		} else if (language == "zh-cn") {
			cout << format("当尝试打开文件 {} 时发生错误. ", args[0]) << endl;
			cout << format("错误信息: {}", args[1]) << endl;
		}
	} else if (message == STDIN_READ_ERROR) {
		/*
		 * args[0] error message
		 */
		if (args.size() != 1) {
			panic();
		}
		if (language == "en-us") {
			cout << "Error when reading from stdin." << endl;
			cout << format("Error message: {}", args[0]) << endl;
		} else if (language == "zh-cn") {
			cout << "当从标准输入读入时发生错误." << endl;
			cout << format("错误信息: {}", args[0]) << endl;
		}
	} else if (message == ARGUMENT_VALUE_ERROR) {
		/*
		 * args[0] function name
		 * args[1] the argument user gave
		 * args[2 to end] available arguments
		 */
		if (args.size() < 3) {
			panic();
		}
		if (language == "en-us") {
			cout << format("Function {} does not receive argument {}. ",  args[0], args[1]) << endl;
			cout << "Available arguments: " << endl;
			for (usize i = 2; i < args.size() - 1; i ++) {
				cout << args[i] << ", ";
			}
			cout << args[args.size() - 1] << endl;
		} else if (language == "zh-cn") {
			cout << format("函数 {} 不接受参数 {}. ",  args[0], args[1]) << endl;
			cout << "可用参数: " << endl;
			for (usize i = 2; i < args.size() - 1; i ++) {
				cout << args[i] << ", ";
			}
			cout << args[args.size() - 1] << endl;
		}
	} else if (message == ARGUMENT_TYPE_ERROR) {
		/*
		 * args[0] function name
		 * args[1] the argument's type
		 * args[2] the argument's value
		 * args[3 to end] available types
		 */
		if (args.size() < 4) {
			panic();
		}
		if (language == "en-us") {
			cout << format("Function {} does not receive argument {}. ",  args[0], args[2]) << endl;
			cout << format("The provided input type '{}' is invalid. ", args[1]) << endl;
			cout << "The function only accepts the following parameter types: " << endl;
			for (usize i = 3; i < args.size() - 1; i ++) {
				cout << args[i] << ", ";
			}
			cout << args[args.size() - 1] << endl;
		} else if (language == "zh-cn") {
			cout << format("函数 {} 不接受参数 {}. ", args[0], args[2]) << endl;
			cout << format("参数的类型 {} 非法. ", args[1]) << endl;
			cout << "该函数只接受以下参数类型: " << endl;
			for (usize i = 3; i < args.size() - 1; i ++) {
				cout << args[i] << ", ";
			}
			cout << args[args.size() - 1] << endl;
		}
	} else if (message == VARIABLE_ALREADY_EXISTS) {
		/*
		 * args[0] variable name
		 */
		if (args.empty()) { // size < 1
			panic();
		}
		if (language == "en-us") {
			cout << format("The variable '{}' is already exist. ", args[0]) << endl;
		} else if (language == "zh-cn") {
			cout << format("变量 {} 已经存在. ", args[0]) << endl;
		}
	} else if (message == VARIABLE_NOT_EXISTS) {
		/*
		 * args[0] variable name
		 */
		if (language == "en-us") {
			cout << format("The variable '{}' is not exist. ", args[0]) << endl;
		} else if (language == "zh-cn") {
			cout << format("变量 {} 不存在. ",  args[0]) << endl;
		}
	}
}