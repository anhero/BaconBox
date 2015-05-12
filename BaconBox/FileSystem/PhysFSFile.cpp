#include "PhysFSFile.h"
#include "BaconBox/Console.h"

using namespace BaconBox;

PhysFSFile::PhysFSFile(const std::string& path, const std::string& mode) : File(path, mode) {
	// TODO : Use mode for r/w/a...
	internal_file = PHYSFS_openRead(path.c_str());
	if (!internal_file) {
		// TODO : Release-mode logger.
#ifdef BB_DEBUG
		PRLN("Reading of `"+path+"` failed.");
		PRLN("Reason: '" << PHYSFS_getLastError() << "'");
#endif
	}
}

File* PhysFSFile::open(const std::string& path, const std::string& mode) {
	PhysFSFile * file = new PhysFSFile(path, mode);
	if (file->internal_file) {
		return file;
	}
	return NULL;
}

PhysFSFile::~PhysFSFile() {
	this->close();
}

void PhysFSFile::close() {
	PHYSFS_close(internal_file);
	internal_file = NULL;
}

size_t PhysFSFile::size() {
	PHYSFS_sint64 len = 0;
	len = PHYSFS_fileLength(internal_file);
	return len;
}

unsigned char* PhysFSFile::toBuffer(unsigned int offset, unsigned int length) {
	if (length == 0) {
		PHYSFS_sint64 max_length = size();
		length = max_length - offset;
	}
	unsigned char* buf = new unsigned char [length];
	PHYSFS_seek(internal_file, offset);
	PHYSFS_read(internal_file, buf, 1, length);
	return buf;
}
int PhysFSFile::fillBuffer(void* buffer, unsigned int offset, unsigned int length) {
	PHYSFS_seek(internal_file, offset);
	return PHYSFS_read(internal_file, buffer, 1, length);
}
