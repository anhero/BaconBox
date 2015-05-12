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
