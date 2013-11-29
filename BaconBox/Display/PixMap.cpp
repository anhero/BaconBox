#include "PixMap.h"

#include <algorithm>

#include "BaconBox/Console.h"
#include "Color.h"
#include "BaconBox/Helper/MathHelper.h"
namespace BaconBox {
	PixMap::PixMap() : width(0), height(0),
		colorFormat(ColorFormat::RGBA), buffer(NULL) {
	}

	PixMap::PixMap(const PixMap &src) : width(src.width),
		height(src.height), colorFormat(src.colorFormat), buffer(NULL) {
		if (src.buffer) {
			unsigned int bufferSize = width * height * ((colorFormat == ColorFormat::RGBA) ? (4) : (1));
			buffer = new uint8_t[bufferSize];

			for (unsigned int i = 0; i < bufferSize; ++i) {
				buffer[i] = src.buffer[i];
			}
		}
	}

	PixMap::PixMap(unsigned int newWidth, unsigned int newHeight,
	               ColorFormat::type newColorFormat) : width(newWidth),
		height(newHeight), colorFormat(newColorFormat),
		buffer(new uint8_t[width *height * ((colorFormat == ColorFormat::RGBA) ? (4) : (1))]) {
	}

	PixMap::PixMap(unsigned int newWidth, unsigned int newHeight,
	               uint8_t defaultValue, ColorFormat::type newColorFormat) :
		width(newWidth), height(newHeight), colorFormat(newColorFormat),
		buffer(new uint8_t[width *height * ((colorFormat == ColorFormat::RGBA) ? (4) : (1))]) {
		unsigned int tmpLength = width * height * ((colorFormat == ColorFormat::RGBA) ? (4) : (1));

		for (unsigned int i = 0; i < tmpLength; ++i) {
			buffer[i] = defaultValue;
		}
	}

	PixMap::PixMap(uint8_t *newBuffer, unsigned int newWidth,
	               unsigned int newHeight, ColorFormat::type newColorFormat) :
		width(newWidth), height(newHeight), colorFormat(newColorFormat),
		buffer(newBuffer) {
	}

	PixMap::~PixMap() {
		if (buffer) {
			delete [] buffer;
		}
	}
	
	void PixMap::setBuffer(uint8_t * buffer){
		this->buffer = NULL;
	}



	void PixMap::convertTo(ColorFormat::type format) {
		uint8_t *tempBuffer = NULL;
		int pixelCount = width * height;
		unsigned int pixelByteSize = PixMap::getPixelByteSize(format);
		unsigned int currentPixelByteSize = getPixelByteSize();

		bool successful = false;

		if (this->colorFormat == ColorFormat::RGBA && format == ColorFormat::ALPHA) {
			tempBuffer = new uint8_t[pixelCount * pixelByteSize];

			for (int i = 0; i < pixelCount; i++) {
				tempBuffer[i] = buffer[i * currentPixelByteSize];
			}

			colorFormat = format;
			successful = true;

		} else if (this->colorFormat == ColorFormat::ALPHA && format == ColorFormat::RGBA) {
			tempBuffer = new uint8_t[pixelCount * pixelByteSize];

			for (int i = 0; i < pixelCount; i++) {
				for (int j = 0; j < 3; j++) {
					tempBuffer[i * 4 + j] = buffer[i];
				}

				tempBuffer[i * 4 + 3] = 255;
			}

			colorFormat = format;
			successful = true;

		} else if(this->colorFormat == ColorFormat::RGBA && format == ColorFormat::RGBA4){
			tempBuffer = new uint8_t[pixelCount * 2];
			
			for (int i = 0; i < pixelCount; i++) {
//				unsigned short pixel = (buffer[i*4] & 0xF0) | (buffer[i*4+1] >> 4) | (buffer[i*4+2] & 0xF0) | (buffer[i*4+3] >> 4);
				uint8_t rg =  (buffer[i*4] & 0xF0) | ((buffer[i*4+1]) >> 4);
				uint8_t ba = (buffer[i*4+2] & 0xF0) | ((buffer[i*4+3])  >> 4);
				unsigned short rgba = rg;
				rgba <<= 8;
				rgba &= 0xFF00;
				rgba  |= ba;
				((unsigned short*)tempBuffer)[i] = rgba;
			}
			
			colorFormat = format;
			successful = true;

		}

		if (successful) {
			delete buffer;
			buffer = tempBuffer;
		}
		else{
			if(tempBuffer) delete tempBuffer;
			Console::error("PixMap::convertTo did't successfully convert to the given color format.");
		}
	}

	void PixMap::makeColorTransparent(const Color &transparentColor) {
		// We make sure the pix map has the right color format.
		if (buffer && colorFormat == ColorFormat::RGBA) {
			unsigned int i = 0;
			unsigned int j;
			size_t index = 0;

			// For each texel.
			while (i < width) {
				j = 0;

				while (j < height) {
					// We check if the color is to be transparent.
					if (std::equal(&buffer[index], &buffer[index] + 3, transparentColor.getComponents())) {
						// We make it completely transparent.
						std::fill(&buffer[index], &buffer[index] + 4, uint8_t(0));
					}

					index += 4;
					++j;
				}

				++i;
			}
		}
		else{
			Console::error("PixMap::makeColorTransparent does not support the given ColorFormat");
		}
	}

	unsigned int PixMap::getWidth() const {
		return width;
	}

	unsigned int PixMap::getHeight() const {
		return height;
	}

	ColorFormat::type PixMap::getColorFormat() const {
		return colorFormat;
	}

	uint8_t *PixMap::getBuffer() {
		return buffer;
	}

	const uint8_t *PixMap::getBuffer() const {
		return buffer;
	}

	void PixMap::insertSubPixMap(const PixMap &subPixMap, unsigned int xOffset,
	                             unsigned int yOffset, bool doubleOutline) {
		if (subPixMap.getColorFormat() == colorFormat) {
			insertSubPixMap(subPixMap.getBuffer(), subPixMap.getWidth(), subPixMap.getHeight(), xOffset, yOffset, doubleOutline);

		} else {
			Console::println("Can't insert sub pixmap into current pixmap, because the color format isn't compatible.");
		}
	}
	unsigned int PixMap::getPixelByteSize(ColorFormat::type colorFormat){
		unsigned int byteSize = 0;
		if (colorFormat == ColorFormat::RGBA) {
			byteSize = 4;
		}
		else if (colorFormat == ColorFormat::RGBA4) {
			byteSize = 2;
		}
		else if (colorFormat == ColorFormat::ALPHA) {
			byteSize = 1;
		}
		return byteSize;
	}

	unsigned int PixMap::getPixelByteSize(){
		return PixMap::getPixelByteSize(colorFormat);
	}

	void PixMap::insertSubPixMap(const uint8_t *subBuffer, unsigned int subWidth,
	                             unsigned int subHeight, unsigned int xOffset,
	                             unsigned int yOffset, bool doubleOutline) {
		if (subWidth > 0u && subHeight > 0u) {
			unsigned int currentWidth = width;
			unsigned int currentHeight = height;

			unsigned int maxX = std::min(subWidth - 1u + xOffset, currentWidth);
			unsigned int maxY = std::min(subHeight - 1u  + yOffset, currentHeight);

			if (maxX > xOffset && maxY > yOffset) {
				unsigned int pixelByteCount = this->getPixelByteSize();
			
				
				
				for (unsigned int i = (doubleOutline && yOffset > 0 ? yOffset-1: yOffset); i <= (doubleOutline && maxY < height ? maxY+1: maxY); ++i) {
					for (unsigned int j = (doubleOutline && xOffset > 0 ? xOffset-1: xOffset); j <= (doubleOutline && maxX < width ? maxX+1: maxX); ++j) {
						for (unsigned int k = 0; k < pixelByteCount; ++k) {
							unsigned int subI;
							unsigned int subJ;
							if(!doubleOutline || (i >= yOffset && i <= maxY)){
								subI = i;
							}
							else{
								subI = MathHelper::clamp(i, yOffset, maxY);
							}
							
							if(!doubleOutline || (j >= xOffset && j <= maxX)){
								subJ = j;
							}
							else{
								subJ = MathHelper::clamp(j, xOffset, maxX);
							}
							
							uint8_t byte = subBuffer[(subWidth * (subI - yOffset) + (subJ - xOffset)) * pixelByteCount + k];
							
							buffer[(i * currentWidth + j) * pixelByteCount + k] = byte;
			
							
						}
					}
				}
			}
		}
	}
}
