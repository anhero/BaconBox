#include <physfs.h>
#include "FileSystem.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"

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
	return (bool)PHYSFS_exists(path.c_str());
}

bool FileSystem::mount(const std::string& what, const std::string& where, const bool append) {
	return FileSystem::getInstance()._mount(what, where, append);
}
bool FileSystem::_mount(const std::string& what, const std::string& where, const bool append) {
	return (bool)PHYSFS_mount(what.c_str(), where.c_str(), append);
}
