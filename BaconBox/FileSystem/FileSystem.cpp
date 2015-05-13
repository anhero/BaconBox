#include <physfs.h>
#include "FileSystem.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"

#include "BaconBox/FileSystem/SystemFS.h"

// TODO : Move to configuration.
#define BB_WITH_PHYSFS

#ifdef BB_WITH_PHYSFS
#include "BaconBox/FileSystem/PhysFSFile.h"
#define FILE_IMPL PhysFSFile
#endif

#ifndef FILE_IMPL
#include "BaconBox/FileSystem/NullFile.h"
// TODO : Make NullFile
#define FILE_IMPL NullFile
#endif

// For the platform save path...
#ifdef BB_IPHONE_PLATFORM
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <stdlib.h>
//#include <sys/stat.h>
//#include <dirent.h>
#elif defined(BB_MAC_PLATFORM) || defined(BB_LINUX) || defined(BB_FLASH_PLATFORM)
#include <pwd.h>
#include <unistd.h>
#endif

#include <sstream>

using namespace BaconBox;

BB_SINGLETON_IMPL(FileSystem);

FileSystem::FileSystem() {
	PHYSFS_init(BaconBox::Engine::getApplicationArgv()[0]);
}

File* FileSystem::open(const std::string &path, const std::string& mode) {
	return FileSystem::getInstance()._open(path, mode);
}
File* FileSystem::_open(const std::string &path, const std::string &mode) {
	return FILE_IMPL::open(path, mode);
}

bool FileSystem::exists(const std::string &path) {
	return FileSystem::getInstance()._exists(path);
}

bool FileSystem::_exists(const std::string &path) {
#ifdef BB_WITH_PHYSFS
	return (bool)PHYSFS_exists(path.c_str());
#endif
}

bool FileSystem::mount(const std::string& what, const std::string& where, const bool write, const bool append) {
	return FileSystem::getInstance()._mount(what, where, write, append);
}

bool FileSystem::_mount(const std::string& what, const std::string& where, const bool write, const bool append) {
#ifdef BB_WITH_PHYSFS
	// TODO : Error handling
	if (write) {
		if (!SystemFS::isDirectory(what)) {
			if (SystemFS::exists(what)) {
				PRLN("Mounting for write failed; `" << what << "` exists, but is not a directory.");
				return false;
			}
			if (!SystemFS::createDirectoryTree(what)) {
				PRLN("Mounting for write failed; `" << what << "` could not create directory tree.");
				return false;
			}
		}
		if (PHYSFS_setWriteDir(what.c_str()) == 0) {
			PRLN("Mounting for write failed; PHYSFS_setWriteDir failed.");
			PRLN("Reason: '" << PHYSFS_getLastError() << "'");
			return false;
		}
		PhysFSFile::setWriteMount(where);
	}
	if (!(bool)PHYSFS_mount(what.c_str(), where.c_str(), append)) {
		PRLN("Mounting `" << what << "` with PHYSFS_mount failed.");
		PRLN("Reason: '" << PHYSFS_getLastError() << "'");
		return false;
	}
	return true;
#endif
}

bool FileSystem::mountDefaultSavePath(const std::string &where) {
	return FileSystem::mount(FileSystem::getPlatformSavePath(), where, true, false);
}

// This might need a bit of refactoring. Especially with regards to the VFS.
// FIXME : 'Dirty', this implements multiple platforms through ifdefs.
// FIXME : 'Dirty', this should only give a path to use, and should not create it.
// Furthermore, I'm pretty sure this is not the right place API-wise to have this.
std::string FileSystem::getPlatformSavePath() {
#if defined(BB_IPHONE_PLATFORM)
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex: 0];
	std::string documentPath = [documentsDirectory cStringUsingEncoding: NSASCIIStringEncoding];
	return documentPath;
#else
	// FIXME : Add back a way to detect a debug document path. Through specific VFS write mounting?
	if (false ) {} //debugDocumentPath != "") { return debugDocumentPath; }
	else {
#if defined(BB_MAC_PLATFORM) || (defined(BB_LINUX) && !defined(BB_ANDROID))

		// Paths relative to the home directory
#if defined(BB_MAC_PLATFORM)
		const std::string conf_dir = "/Library/Application Support/";
#else
		// TODO: Implement XDG Basedir properly.
		const std::string conf_dir = "/.config/";
#endif
		// Basically does this :
		//      $HOME/conf_dir/$APPLICATION_NAME/
		static bool firstTime = true;
		std::stringstream ss;
		ss << getpwuid(getuid())->pw_dir << conf_dir << Engine::getApplicationName() << "/";
		// Always tries to create the folder the first time this is ran.
		if (firstTime) {
			SystemFS::createDirectory(ss.str());
			firstTime = false;
		}
		return ss.str();

#elif defined(BB_ANDROID)
		return "/data/data/" + AndroidHelper::getPackageName() + "/";
#else
		return std::string();
#endif
	}
#endif
}
