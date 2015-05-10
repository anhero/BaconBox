#include "File.h"

using namespace BaconBox;

File::File(const std::string& path, const std::string &mode) {
	this->path = path;
	this->mode = mode;
}
File::~File() {}

size_t File::size() {return 0;}
unsigned char* File::toBuffer(unsigned int offset, unsigned int length) {return NULL;}

