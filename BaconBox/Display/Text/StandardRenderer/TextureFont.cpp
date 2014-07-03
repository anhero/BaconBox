#include "BaconBox/Display/Text/StandardRenderer/TextureFont.h"
#include "BaconBox/Components/StandardRenderer/TextRenderer.h"

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