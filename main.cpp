#include "include/define.h"
#include "include/include.h"
#include "locales/error.h"
#include "locales/info.h"
#include "locales/language.h"
#include "tools/arguments.h"
#include "tools/reader.h"
#include "tools/spliter.h"
#include "variables/bigint.h"
void run(const string &content) {
	
}

int main(const int argc, const char * argv[]) {
	for (int i = 0; i < argc; i ++) {
		if (const string &arg = argv[i]; arg.substr(0, 2) == "--") {
			argument(arg.substr(2));
		} else {
			const auto [content, err] = reader::get_file_content(arg);
			if (err) {
				return -1;
			}
			run(content);
		}
	}
	if (argc != 1) {
		return 0;
	}
	info(INFO_VERSION);
	while (true) {
		const auto [str_content, err] = reader::get_stdin_line();
		if (err) {
			continue;
		}
		const vector <string> states = spliter::split_line_into_words(str_content);

	}
}