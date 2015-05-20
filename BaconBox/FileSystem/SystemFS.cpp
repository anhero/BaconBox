#include "BaconBox/FileSystem/SystemFS.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"

#if defined(BB_MAC_PLATFORM) \
	|| defined(BB_LINUX) \
	|| defined(BB_WINDOWS_PLATFORM) // Windows platform is for mingw.
									// FIXME : Make a MINGW32 platform and use it.
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif

using namespace BaconBox;

SystemFS::SystemFS() {}

bool SystemFS::exists(const std::string &path) {
#ifdef BB_IPHONE_PLATFORM
	// TODO (2015-05-12) : Should we really always return false on iOS?
	return false;
#elif defined(BB_MAC_PLATFORM) || defined(BB_LINUX) || defined(BB_WINDOWS_PLATFORM)
	struct stat st;
	return stat(path.c_str(), &st) == 0;
#else
	Console__error("Call to non-implemented SystemFS::exists()");
	return false;
#endif
}

bool SystemFS::isDirectory(const std::string &path) {
#if defined(BB_MAC_PLATFORM) || defined(BB_LINUX) || defined(BB_WINDOWS_PLATFORM) || defined(BB_IPHONE_PLATFORM)
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
	if (::mkdir(path.c_str(), 0755)) {
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
	bool failed = false;

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
		while (!failed && i != path.end()) {
			tmpPath.append(1, *i);
			// If we encounter a slash and the folder doesn't already exist,
			// we try to create the folder.
			if (*i == '/' && !isDirectory(tmpPath) && createDirectory(tmpPath)) {
				Console::print("Failed to create the following directory \"");
				Console::print(tmpPath);
				Console::println("\".");
				failed = true;
			}
			++i;
		}

		// If the path didn't end with a slash, we try to create the last
		// folder.
		if (!failed && tmpPath.at(tmpPath.size() - 1) != '/' && !isDirectory(tmpPath) && createDirectory(tmpPath)) {
			Console::print("Failed to create the following directory \"");
			Console::print(tmpPath);
			Console::println("\".");
			failed = true;
		}
	}

	return !failed;
}

// TODO : Refactor using SystemFS traversal and delete functions.
bool SystemFS::removeDirectoryTree(const std::string &path) {
	// #if defined(BB_FLASH_PLATFORM)
	// 	return false;
	// #else
	// Took from here: http://stackoverflow.com/questions/2256945/removing-a-non-empty-directory-programmatically-in-c-or-c
	DIR *d = opendir(path.c_str());
	size_t path_len = strlen(path.c_str());
	int r = -1;
	if (d) {
		struct dirent *p;
		r = 0;
		while (!r && (p=readdir(d))) {
			int r2 = -1;
			char *buf;
			size_t len;
			/* Skip the names "." and ".." as we don't want to recurse on them. */
			if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
				continue;
			}
			len = path_len + strlen(p->d_name) + 2;
			buf = (char*)malloc(len);
			if (buf) {
				struct stat statbuf;
				snprintf(buf, len, "%s/%s", path.c_str(), p->d_name);
				if (!stat(buf, &statbuf)) {
					if (S_ISDIR(statbuf.st_mode)) {
						// If it's a directory, recurse with this function in it.
						r2 = removeDirectoryTree(buf);
					}
					else {
						r2 = unlink(buf);
					}
				}
				free(buf);
			}
			r = r2;
		}
		closedir(d);
	}
	if (!r) {
		r = rmdir(path.c_str());
	}
	return r;
	// #endif
}


// Aliases
bool SystemFS::mkdir(const std::string &path) { return createDirectory(path); }
bool SystemFS::mkdir_p(const std::string &path) { return createDirectoryTree(path); }
