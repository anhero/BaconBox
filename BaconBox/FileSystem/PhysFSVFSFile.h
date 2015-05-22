#ifndef PhysFSVFSFile_H
#define PhysFSVFSFile_H

#include "BaconBox/FileSystem/File.h"
#include <physfs.h>

#ifdef BB_ANDROID
#include <android/asset_manager.h>
#endif

namespace BaconBox {
	class FileSystem;
	/**
	 * Implementation of BaconBox::File for PhysicsFS.
	 */
	class PhysFSVFSFile : public File {
		friend class FileSystem;
	public:
		virtual ~PhysFSVFSFile();
		virtual unsigned char* toBuffer(unsigned int offset = 0, unsigned int length = 0);
		virtual int fillBuffer(void* buffer, unsigned int offset = 0, unsigned int length = 0);
		virtual size_t size();
		virtual int seek(unsigned int offset = 0);
		virtual int tell();
		virtual std::string read(unsigned int to_read = 0);
		virtual bool write(const std::string data);

		static File * open(const std::string& path, const std::string& mode);
		virtual void close();

		/// Used internally to keep the writedir and readdir "mounted" at the same place.
		static void setWriteMount(const std::string& where);

#ifdef BB_ANDROID
		/**
		 * Used to get a FD on Android with the Android Assets Manager.
		 * This is particular in that this will work only on uncompressed files.
		 * See include/android/asset_manager.h, comment for AAsset_openFileDescriptor.
		 * To add files other than the defaults, look at configuring aapt.
		 * It defaults to uncompressed for a couple of default media files.
		 *
		 * @param outStart Out value of the start of the FD
		 * @param outLength Out value of the length of the FD
		 */
		int toAndroidFD(off_t* outStart, off_t* outLength);
#endif

	protected:
		PhysFSVFSFile(const std::string& path, const std::string& mode);
		PHYSFS_file* internal_file;

		/// Used internally, see: setWriteMount();
		static std::string write_mount_point;
	};
}

#endif // PhysFSVFSFile_H
