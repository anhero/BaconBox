#include "BaconBox/FileSystem/SystemFS.h"

#include "BaconBox/Console.h"


#if defined(BB_MAC_PLATFORM) || defined(BB_LINUX)
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

using namespace BaconBox;

SystemFS::SystemFS() {}

bool SystemFS::exists(const std::string &path) {
#ifdef BB_IPHONE_PLATFORM
	// TODO (2015-05-12) : Should we really always return false on iOS?
	return false;
#elif defined(BB_MAC_PLATFORM) || defined(BB_LINUX)
	struct stat st;
	return stat(path.c_str(), &st) == 0;
#else
	Console__error("Call to non-implemented SystemFS::exists()");
	return false;
#endif
}

bool SystemFS::isDirectory(const std::string &path) {
#ifdef BB_IPHONE_PLATFORM
	// TODO (2015-05-12) : Should we really always return false on iOS?
	return false;
#elif defined(BB_MAC_PLATFORM) || defined(BB_LINUX)
	struct stat st;
	if (stat(path.c_str(), &st) != 0) {
		// TODO : Error handling; it would be nice to give the error to the user.
		//PRLN(strerror(errno));
		return false;
	}
	else if (st.st_mode & S_IFDIR) {
		return true;
	}
	else {
		return false;
	}
#else
	Console__error("Call to non-implemented SystemFS::isDirectory()");
	return false;
#endif
}

bool SystemFS::createDirectory(const std::string &path) {
#if defined(BB_MAC_PLATFORM) || defined(BB_LINUX)|| defined(BB_IPHONE_PLATFORM)
	if (mkdir(path.c_str(), 0755)) {
		return true;
	} else {
		return false;
	}
#else
	Console__error("Call to non-implemented SystemFS::createDirectory()");
	return false;
#endif
}

bool SystemFS::createDirectoryTree(const std::string &path) {
	bool result = false;

	// We make sure the path isn't empty.
	if (!path.empty()) {
		std::string::const_iterator i = path.begin();
		std::string tmpPath;
		tmpPath.reserve(path.size());

#ifdef BB_WINDOWS_PLATFORM
		if (path.size() >= 2 && path.at(1) == ':' && ((path.at(0) >= 'A' && path.at(0) <= 'Z') || (path.at(0) >= 'a' && path.at(0) <= 'z'))) {
			tmpPath.append(path, 0, 2);
			++i;
			++i;
		}
#endif

		// For each character in the path.
		while (!result && i != path.end()) {
			tmpPath.append(1, *i);
			// If we encounter a slash and the folder doesn't already exist,
			// we try to create the folder.
			if (*i == '/' && !isDirectory(tmpPath) && createDirectory(tmpPath)) {
				Console::print("Failed to create the following directory \"");
				Console::print(tmpPath);
				Console::println("\".");
				result = true;
			}
			++i;
		}

		// If the path didn't end with a slash, we try to create the last
		// folder.
		if (!result && tmpPath.at(tmpPath.size() - 1) != '/' && !isDirectory(tmpPath) && createDirectory(tmpPath)) {
			Console::print("Failed to create the following directory \"");
			Console::print(tmpPath);
			Console::println("\".");
			result = true;
		}
	}

	return result;
}

