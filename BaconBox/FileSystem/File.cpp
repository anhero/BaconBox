#include "File.h"

using namespace BaconBox;

File::File(const std::string& path, const std::string &mode) {
	this->path = path;
	this->mode = mode;
}
File::~File() {}

// /////////////////////////////////////////////////////////////////////////////
// MemBuf

File::MemBuf::MemBuf(File *f) : buf(NULL) {
	buf = (char*)f->toBuffer();
	char* begin = buf;
	char* end = begin + f->size();
	this->setg(begin, begin, end);
}

File::MemBuf::~MemBuf() {
	delete[] buf;
}
