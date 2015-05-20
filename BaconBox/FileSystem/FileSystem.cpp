#include "BaconBox/FileSystem/FileSystem.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"

#include "BaconBox/PlatformFlagger.h"

#include BB_VFS_INCLUDE

using namespace BaconBox;

FileSystem::FileSystem() {}

File* FileSystem::open(const std::string &path, const std::string& mode) {
	return BB_VFS_IMPL->open(path, mode);
}
bool FileSystem::exists(const std::string &path) {
	return BB_VFS_IMPL->exists(path);
}
bool FileSystem::mount(const std::string& what, const std::string& where, const bool write, const bool append) {
	return BB_VFS_IMPL->mount(what, where, write, append);
}

/******************************************************************************/
/*                      Platform-dependent save path                          */
/******************************************************************************/

bool FileSystem::mountDefaultSavePath(const std::string &where) {
	return FileSystem::mount(FileSystem::getPlatformSavePath(), where, true, false);
}

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

#ifdef BB_ANDROID
#include "BaconBox/Helper/Android/AndroidHelper.h"
#endif

// Force include the SystemFS as it is needed for some operations.
#include "BaconBox/FileSystem/SystemFS.h"

#include <sstream>

// This might need a bit of refactoring. Especially with regards to the VFS.
// FIXME : 'Dirty', this implements multiple platforms through ifdefs.
// FIXME : 'Dirty', this should only give a path to use, and should not create it.
// Furthermore, I'm pretty sure this is not the right place API-wise to have this.
// FIXME : No windows implementation yet!
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
			SystemFS::createDirectoryTree(ss.str());
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
