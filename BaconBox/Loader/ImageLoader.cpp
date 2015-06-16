#include "ImageLoader.h"

#include "BaconBox/Console.h"

#include <cassert>
#include <cstring>

using namespace BaconBox;

ImageLoader::ImageLoader() {}

PixMap* ImageLoader::load(const std::string &path) {
	// For now, as we only support loading PNG files, we
	// can shortcircuit any testing and directly use loadFromPNG().
	#ifdef BB_WITH_PNG
	return loadFromPNG(path);
	#endif
	return NULL;
}

#ifdef BB_WITH_PNG
PixMap* ImageLoader::loadFromPNG(const std::string &path) {
	// Create a status struct later one used to stream the PNG file.
	png_buf_read_status status = png_buf_read_status(FileSystem::open(path));

	// Get the header
	unsigned char* png_header= status.file->toBuffer(0, PNG_HEADER_SIZE);
	// And the total size
	unsigned int png_data_size = status.file->size();

	// FIXME : replace assert with checks and messages.
	// Do some sanity checking.
	if (!(png_header != NULL && png_data_size > PNG_HEADER_SIZE) || !(png_sig_cmp((png_const_bytep)png_header, 0, PNG_HEADER_SIZE) == 0)) {
#if BB_DEBUG
		Console__error("The PNG file does not seem to be valid.");
		Console__error(" File : " + path);
#endif
		delete[] png_header;
		return NULL;
	}
	delete[] png_header;

	// We've already read some of the file.
	status.bytes_read = PNG_HEADER_SIZE;

	// FIXME : Error handling
	png_structp PNG_reader = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (PNG_reader == NULL) {
#if BB_DEBUG
		Console__error("The PNG file does not seem to be valid.");
		Console__error(" File : " + path);
#endif
		return NULL;
	}

	// FIXME : Error handling
	png_infop PNG_info = png_create_info_struct(PNG_reader);
	if (PNG_info == NULL) {
#if BB_DEBUG
		Console__error("The PNG file does not seem to be valid.");
		Console__error(" File : " + path);
#endif
		png_destroy_read_struct(&PNG_reader, NULL, NULL);
		return NULL;
	}

	png_infop PNG_end_info = png_create_info_struct(PNG_reader);
	if (PNG_end_info == NULL) {
#if BB_DEBUG
		Console__error("The PNG file does not seem to be valid.");
		Console__error(" File : " + path);
#endif
		png_destroy_read_struct(&PNG_reader, &PNG_info, NULL);
		return NULL;
	}

	if (setjmp(png_jmpbuf(PNG_reader))) {
		Console::println("Cannot load this png file " + path);
		png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
		return NULL;
	}

	// Gets libpng reading from our data buffer.
	png_set_read_fn(PNG_reader,(png_voidp)&status, ImageLoader::png_read_data);

	// Tells libpng we have already read the header
	png_set_sig_bytes(PNG_reader, PNG_HEADER_SIZE);

	png_read_info(PNG_reader, PNG_info);
	png_uint_32 width, height;
	width = png_get_image_width(PNG_reader, PNG_info);
	height = png_get_image_height(PNG_reader, PNG_info);
	png_uint_32 bit_depth, color_type;
	bit_depth = png_get_bit_depth(PNG_reader, PNG_info);
	color_type = png_get_color_type(PNG_reader, PNG_info);

	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(PNG_reader);
	}

	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(PNG_reader);
	}

	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(PNG_reader);
	}

	if (png_get_valid(PNG_reader, PNG_info, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(PNG_reader);
	}
	else {
		png_set_filler(PNG_reader, 0xff, PNG_FILLER_AFTER);
	}

	if (bit_depth == 16) {
		png_set_strip_16(PNG_reader);
	}

	png_read_update_info(PNG_reader, PNG_info);
	png_byte *PNG_image_buffer = new png_byte[4 * width * height];
	png_byte **PNG_rows = (png_byte **)malloc(height * sizeof(png_byte *));
	unsigned int row;

	for (row = 0; row < height; ++row) {
		PNG_rows[row] = PNG_image_buffer + (row * 4 * width);
	}

	png_read_image(PNG_reader, PNG_rows);
	free(PNG_rows);
	png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);

	PixMap *aPixMap = new PixMap(PNG_image_buffer, width, height);
	return aPixMap;
}

void ImageLoader::png_read_data(png_structp png_ptr, png_bytep data, png_size_t length) {
	// Get back what we stowed away in the reader
	png_buf_read_status * status = (png_buf_read_status *)png_get_io_ptr(png_ptr);
	// Fill in a C-style array with the wanted offset
	unsigned char* png_data = status->file->toBuffer(status->bytes_read, length);
	// Copy it over
	memcpy(data, png_data, length);
	//
	status->bytes_read = status->bytes_read + length;
	delete[] png_data;
}
#endif
