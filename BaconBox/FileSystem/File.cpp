#include "File.h"

using namespace BaconBox;

File* File::open(const std::string &path, const std::string &mode) {
	return NULL;
}

File::File(const std::string& path, const std::string &mode) {
	this->path = path;
	this->mode = mode;
}
File::~File() {}

size_t File::size() {return 0;}
unsigned char* File::toBuffer(unsigned int offset, unsigned int length) {return NULL;}
int File::fillBuffer(void* buffer, unsigned int offset, unsigned int length) {return 0;}
void File::close() {}

// /////////////////////////////////////////////////////////////////////////////
// MemBuf

File::MemBuf::MemBuf(File *f) : buf(NULL) {
	char* begin = (char*)f->toBuffer();
	char* end = begin + f->size();
	this->setg(begin, begin, end);
}

File::MemBuf::~MemBuf() {
	delete buf;
}
