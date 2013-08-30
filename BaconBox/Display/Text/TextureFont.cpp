#include "BaconBox/Display/Text/TextureFont.h"
#include "BaconBox/Components/TextRenderer.h"

namespace BaconBox {
		TextureFont::TextureFont():charsMap(), kerningMap(), lineHeight(0){}
		TextureFont::TextureFont(const std::string &newName):Font(newName), charsMap(), kerningMap(), lineHeight(0), pixelSize(0){}
		int TextureFont::getLineHeight(){
		    return lineHeight;
		}
	int TextureFont::getPixelSize(){
		return pixelSize;
	}

		
}