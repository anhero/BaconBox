#include "PhysFSFile.h"
#include "BaconBox/Console.h"

using namespace BaconBox;

std::string PhysFSFile::write_mount_point;

void PhysFSFile::setWriteMount(const std::string &where) {
	PhysFSFile::write_mount_point = where;
}

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

int PhysFSFile::seek(unsigned int offset) {
	int ret = PHYSFS_seek(internal_file, offset);
	if (ret == 0) {
		return offset;
	}
	// TODO : Error handling/logging.
	return -1;
}

int PhysFSFile::tell() {
	int ret = PHYSFS_tell(internal_file);
	if (ret >= 0) {
		return ret;
	}
	// TODO : Error handling/logging.
	return -1;
}

unsigned char* PhysFSFile::toBuffer(unsigned int offset, unsigned int length) {
	// If the length is zero, assume read all.
	if (length == 0) {
		PHYSFS_sint64 max_length = size();
		length = max_length - offset;
	}
	// If still, the length is zero, this is a zero-length read.
	if (length == 0) {
		return NULL;
	}
	unsigned char* buf = new unsigned char [length]();
	PHYSFS_seek(internal_file, offset);
	int amount_read = PHYSFS_read(internal_file, buf, 1, length);
	if (amount_read < 0) {
		PRLN(PHYSFS_getLastError());
		return NULL;
	}
	return buf;
}

int PhysFSFile::fillBuffer(void* buffer, unsigned int offset, unsigned int length) {
	PHYSFS_seek(internal_file, offset);
	return PHYSFS_read(internal_file, buffer, 1, length);
}

std::string PhysFSFile::read(unsigned int to_read) {
	unsigned int bytes_left = size() - tell();
	if (to_read == 0 || to_read > bytes_left) {
		to_read = bytes_left;
	}
	char * buf = (char*)toBuffer(tell(), to_read);
	// On empty read, the buf* is NULL.
	if (!buf) { buf = new char[1](); }
	std::string str(buf);
	delete[] buf;
	return str;
}
