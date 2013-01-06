#include "BaconBox/Console.h"

using namespace BaconBox;

void Console::printTrace(int max) {
#ifndef BB_ANDROID
	Console::print_stacktrace(stdout, max);
#endif
}

void Console::_log(std::string file, int line,std::string varname, std::string value) {
#ifndef BB_ANDROID
	std::cout << file << "@" << line << ": " << varname << " == " << value << std::endl;
#endif
}

void Console::_print(std::string file, int line, std::string text) {
#ifndef BB_ANDROID
	std::cout << file << "@" << line << ": " << text << std::endl;
#endif
}

void Console::_printf(std::string file, int line, std::string formatString, ...) {
#ifndef BB_ANDROID
	va_list args;
	va_start(args, formatString);
	std::cout << file << "@" << line << ": ";
	vfprintf(stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end(args);
#endif
}

void Console::printf(std::string formatString, ...) {
#ifndef BB_ANDROID
	va_list args;
	va_start(args, formatString);
	vfprintf(stdout, formatString.c_str(), args);
	std::cout << std::endl;
	va_end(args);
#endif
}
