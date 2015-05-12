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
		 * Loads a file to a passed C-style buffer.
		 * This can be dangerous if you read all into a buffer not sized properly.
		 * @param offset Offset to start at, in bytes
		 * @param length Length to read. Zero (0) means read all. (CAUTION!)
		 * @return The amount of data read.
		 */
		virtual int fillBuffer(void* buffer, unsigned int offset = 0, unsigned int length = 0);
		/**
		 * @return The file size in bytes.
		 */
		virtual size_t size();
		/**
		 * Gets the internal file pointer to a certain offset in the file.
		 * The seek is relative to the start of the file.
		 * @param offset Offset to go to.
		 * @return
		 */
		virtual int seek(unsigned int offset = 0);
		/**
		 * Gets where we are seeked in the file.
		 * @return Amount of bytes in.
		 */
		virtual int tell();
		/**
		 * Reads the file from currently seeked position, for to_read bytes.
		 * An amount of data to read of zero means until the end of the file.
		 * @param to_read Amount of data to read.
		 * @return A string with the contents needed.
		 */
		virtual std::string read(unsigned int to_read = 0);
		/**
		 * Writes a data string to a file.
		 * @param data String of data to write.
		 * @return Whether it succeded or not.
		 */
		virtual bool write(const std::string data);

		/**
		 * Closes the file.
		 */
		virtual void close();
		virtual ~File();

		/**
		 * Opens a File on the VFS.
		 * @param path Path to open.
		 * @param mode Mode to open, "r", "w" or "a". Defaults to "r".
		 * @return The pointer to the opened File.
		 */
		static File * open(const std::string& path, const std::string& mode);
	protected:
		File(const std::string& path, const std::string& mode);
		std::string path;
		std::string mode;
	};
}
#endif // FILE_H
