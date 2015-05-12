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
int File::tell() {return 0;}
int File::seek(unsigned int offset) {return 0;}
std::string File::read(unsigned int to_read) {return "";}
void File::close() {}

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
