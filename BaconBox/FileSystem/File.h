#ifndef FILE_H
#define FILE_H
#include <string>
#include <streambuf>

namespace BaconBox {
	class FileSystem;
	class File {
		friend class FileSystem;
	public:
		/**
		 * Implementation of a streambuf that works on a C-style array.
		 * This is a quick and dirty hack, mostly.
		 */
		struct MemBuf : std::streambuf {
		public:
			/**
			 * Creates an internal buffer from the file passed.
			 * @param f Pointer to a file, no reference is kept.
			 */
			MemBuf(File* f);
			~MemBuf();
		private:
			char* buf;
		};

		/**
		 * Loads a file to a C-style buffer.
		 * @param offset Offset to start at, in bytes
		 * @param length Length to read. Zero (0) mean read all.
		 * @return The pointer to the buffer. You need to manage that pointer!
		 */
		virtual unsigned char* toBuffer(unsigned int offset = 0, unsigned int length = 0);
		/**
		 * @return The file size in bytes.
		 */
		virtual size_t size();
		virtual ~File();
	protected:
		File(const std::string& path, const std::string& mode);
		std::string path;
		std::string mode;
	};
}
#endif // FILE_H
