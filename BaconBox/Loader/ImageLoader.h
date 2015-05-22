#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "BaconBox/Display/PixMap.h"
#include "BaconBox/FileSystem/FileSystem.h"

// TODO: See if we replace with something like BB_WITH_PNG ?
#if ! defined(BB_FLASH_PLATFORM)
	//For LibPNG
	#include <png.h>
	#define PNG_HEADER_SIZE 8
#endif

namespace BaconBox {
	/**
	 * Class hosting the helpers to load Images as PixMaps.
	 *
	 * Do note that any path here are resolved through the BaconBox FileSystem helper.
	 * This means that it will load from any VFS currently used.
	 * This also means that using the usual "file" functions is not recommended.
	 * Instead, load the file to a C-style buffer or through a stream buffer.
	 *
	 * You should not have to rely on calling a specific method and should
	 * always call load(), as it should resolve the filetype properly.
	 */
	class ImageLoader
	{
	public:
		/**
		 * Tries as hard as it can to take the path given and load it as a PixMap.
		 * Tries first guessing through the file extension, then if wrong, will
		 * look at the magic numbers.
		 *
		 * @FIXME For now, calls loadFromPNG directly as it is the only file format supported.
		 *
		 * @param path PixMap source file.
		 * @return Valid PixMap or NULL.
		 */
		static PixMap* load(const std::string &path);

		/**
		 * Loads a PNG file as a PixMap, unless it cannot.
		 * @param path PixMap source file.
		 * @return Valid PixMap or NULL.
		 */
		static PixMap* loadFromPNG(const std::string &path);
	private:
		ImageLoader();

		/// Used internally to read data from memory.
		static void png_read_data(png_structp png_ptr, png_bytep data, png_size_t length);

		/// Used internally by the png reader code.
		struct png_buf_read_status {
			// Bytes read
			unsigned int bytes_read;
			// Pointer to the file
			File* file;
			png_buf_read_status(File* file) : file(file), bytes_read(0) {}
			~png_buf_read_status() { delete file; }
		};
	};
}

#endif // IMAGELOADER_H
