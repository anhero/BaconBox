/**
 * @file
 * @ingroup Display
 */
#ifndef BB_COLORFORMAT_H
#define BB_COLORFORMAT_H

#include <string>

namespace BaconBox {
		struct ColorFormat {
		enum type {
			NONE,
			RGBA,
			ALPHA,
			RGBA4
		};

		static ColorFormat::type colorFormatFromString(const std::string & format);
	private:
		ColorFormat();
	};
	
}

#endif
