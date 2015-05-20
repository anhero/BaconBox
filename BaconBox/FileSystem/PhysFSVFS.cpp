#include <physfs.h>
#include "BaconBox/FileSystem/PhysFSVFS.h"
#include "BaconBox/FileSystem/PhysFSVFSFile.h"
#include "BaconBox/FileSystem/SystemFS.h"

#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"

using namespace BaconBox;

BB_SINGLETON_IMPL(PhysFSVFS)

PhysFSVFS::PhysFSVFS() {
	Console__log("PhysFS::PhysFS()");
	int ret;
	// Some platforms might not have an Argv.
	if (BaconBox::Engine::getApplicationArgv()) {
		ret = PHYSFS_init(BaconBox::Engine::getApplicationArgv()[0]);
	}
	else {
		ret = PHYSFS_init(NULL);
	}
	if (ret == 0) {
		PRLN("Initialization of PhysicsFS failed:");
		PRLN("	Reason: '" << PHYSFS_getLastError() << "'");
		// should abort?
	}
}

bool PhysFSVFS::exists(const std::string &path) {
	return (bool)PHYSFS_exists(path.c_str());
}
bool PhysFSVFS::mount(const std::string &what, const std::string &where, const bool write, const bool append) {
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
			PRLN("Mounting for write failed; (`" << what << "`)  PHYSFS_setWriteDir failed.");
			PRLN("Reason: '" << PHYSFS_getLastError() << "'");
			return false;
		}
		PhysFSVFSFile::setWriteMount(where);
	}
	if (!(bool)PHYSFS_mount(what.c_str(), where.c_str(), append)) {
		PRLN("Mounting `" << what << "` with PHYSFS_mount failed.");
		PRLN("Reason: '" << PHYSFS_getLastError() << "'");
		return false;
	}
	return true;
}
File* PhysFSVFS::open(const std::string &path, const std::string &mode) {
	return PhysFSVFSFile::open(path, mode);
}
