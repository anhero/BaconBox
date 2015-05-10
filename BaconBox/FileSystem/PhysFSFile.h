#ifndef PHYSFSFILE_H
#define PHYSFSFILE_H

#include "BaconBox/FileSystem/File.h"
#include <physfs.h>

namespace BaconBox {
	class FileSystem;
	/**
	 * Implementation of BaconBox::File for PhysicsFS.
	 */
	class PhysFSFile : public File {
		friend class FileSystem;
	public:
		~PhysFSFile();
		virtual unsigned char* toBuffer(unsigned int offset = 0, unsigned int length = 0);
		virtual size_t size();
	protected:
		PhysFSFile(const std::string& path, const std::string& mode);
		PHYSFS_file* internal_file;
	};
}

#endif // PHYSFSFILE_H
