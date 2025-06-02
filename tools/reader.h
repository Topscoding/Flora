#pragma once
#include "../include/include.h"
#include "../locales/error.h"

// If you see the return argument "pair <xxx, bool>", the second argument is whether went error.
// True means error, and false means nothing unexceptional happened.
class reader {
public:
	static pair <string, bool> get_stdin_still_end_sign(const string &end_sign) {
		try {
			string content, line;
			while (getline(cin, line)) {
				if (line == end_sign) {
					break;
				}
				content.append(line);
				content.push_back('\n');
			}
			return make_pair(content, false);
		} catch (const exception &e) {
			error(ERROR_STDIN_READ_ERROR, {e.what()});
			return make_pair(string(e.what()), true);
		}
	}
	static pair <string, bool> get_stdin_line() {
		try {
			string content;
			getline(cin, content);
			return make_pair(content, false);
		} catch (const exception &e) {
			error(ERROR_STDIN_READ_ERROR, {e.what()});
			return make_pair(string(e.what()), true);
		}
	}
	static pair <string, bool> get_file_content(const string &file_path) {
		// Open the file
		// 打开文件
		ifstream reader(file_path);
		if (!reader.is_open()) {
			error(ERROR_FILE_OPEN_ERROR, {file_path, strerror(errno)});
			return make_pair("", true);
		}
		string content, line;
		while (getline(reader, line)) {
			content.append(line);
			content.push_back('\n');
		}
		reader.close();
		return make_pair(content, false);
	}
};