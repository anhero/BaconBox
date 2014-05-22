#ifndef BB_CONSOLE_H
#define BB_CONSOLE_H

#include "BaconBox/PlatformFlagger.h"

// @TODO: Backtrace magic for other platforms than GCC... (clang?, msvc)
// @TODO: Stack trace in an object to allow more manipulation?

#include "BaconBox/PlatformFlagger.h"

#ifdef BB_ANDROID
#include <android/log.h>
#else
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#endif

#include <iostream>
//#endif

#include <string>
#include <sstream>

#ifdef BB_LUA
#include "BaconBox/Script/Lua/LuaManager.h"
#endif

// Defines for line numbers and filename...
// Sadly, can't be done by some other magic...
#define Console__print(a)    Console::_print(__FILE__, __LINE__, a);
#define Console__printf(...) Console::_printf(__FILE__, __LINE__, __VA_ARGS__);
#define Console__log(a)      Console::_log(__FILE__, __LINE__, #a, a);

#ifndef BB_ANDROID
#define Console__error(a)    std::cerr << "Error: " << a << std::endl
#else
#define Console__error(a){std::cerr << "Error: " << a << std::endl; BaconBox::Console::logcatSS.str(""); BaconBox::Console::logcatSS << a; BaconBox::Console::logcatBuffer = BaconBox::Console::logcatSS.str(); __android_log_print(ANDROID_LOG_WARN, LOG_TAG, BaconBox::Console::logcatBuffer.c_str());}
#endif


#ifndef BB_ANDROID
#define PRLN(a) std::cout << a << std::endl
#else
#define  LOG_TAG    "BaconBox"
#define PRLN(a) {std::cout << a << std::endl; BaconBox::Console::logcatSS.str(""); BaconBox::Console::logcatSS << a; BaconBox::Console::logcatBuffer = BaconBox::Console::logcatSS.str(); __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, BaconBox::Console::logcatBuffer.c_str());}
#endif


#ifdef BB_ANDROID
#define PV(x) PRLN(#x << ": " << x);
#else

#define PV(x) std::cout << #x << ": " << x << std::endl
#endif

namespace BaconBox {
	class Console {
	public:
		
#ifdef BB_ANDROID
		static std::stringstream logcatSS;
		static std::string logcatBuffer;
#endif
		/**
		 * Prints text in the console. Adds a new line at the end.
		 *
		 * @param input Value to print.
		 */
		template <typename T>
		static void println(const T& input) {
#ifndef BB_ANDROID
			std::cout << input << std::endl;
#endif
		}

		/**
		 * Prints text in the console.
		 *
		 * @param input Value to print.
		 */
		template <typename T>
		static void print(const T& input) {
#ifndef BB_ANDROID
			std::cout << input;
#endif
		}

		/**
		 * Prints warning information on the console.
		 *
		 * This usually only differ by style.
		 *
		 * @param input Text to print.
		 */
		template <typename T>
		static void warn(const T& input) {
#ifndef BB_ANDROID
			std::cout << "Warn: " << input << std::endl;
#endif
		}

		/**
		 * Prints information on the console.
		 *
		 * This usually only differ by style.
		 *
		 * @param input Text to print.
		 */
		template <typename T>
		static void info(const T& input) {
#ifndef BB_ANDROID
			std::cout << "Info: " << input << std::endl;
#endif
		}

		/**
		 * Prints error information on the console.
		 *
		 * This usually only differ by style.
		 *
		 * @param input Text to print.
		 */
		template <typename T>
		static void error(const T& input) {
#ifndef BB_ANDROID
			#ifdef BB_LUA
				LuaManager::error(Console::toString(input));
			#else
				std::cerr << "Error: " << input << std::endl;
			#endif
#endif
		}

		/**
		 * Used by the macro to print text with file and line number information.
		 *
		 * @param file Filename of caller.
		 * @param line Line number of caller.
		 * @param text Text to print.
		 */
		static void _print(std::string file, int line, std::string text);

		/**
		 * Used by the macro to print variable name and value with file and line number information.
		 *
		 * @param file Filename of caller.
		 * @param line Line number of caller.
		 * @param varname Name of the variable to print.
		 * @param value Value of the printed variable
		 */
		static void _log(std::string file, int line, std::string varname,
		                 std::string value);



		/**
		 * Prints formatted as printf would.
		 *
		 * @param formatString Format string, as in printf.
		 * @param ... Things as parameters.
		 */
		 
		static void printf(std::string formatString, ...);

		/**
		 * Used by the macro to print formatted text with file and line number information.
		 *
		 * @param file Filename of caller.
		 * @param line Line number of caller.
		 * @param formatString Format string, as in printf.
		 * @param ... Things as parameters.
		 */
		static void _printf(std::string file, int line, std::string formatString, ...);

		/**
		 * Convert type to string.
		 */
		template<class T> static std::string toString(T i) {
			std::stringstream ss;
			ss << i;
			return ss.str();
		}
	private:

	};
}


#endif // CONSOLE_H
