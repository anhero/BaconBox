#include "BaconBox/Display/Text/TextureFont.h"
#include "Components/TextRenderer.h"

namespace BaconBox {
		TextureFont::TextureFont():charsMap(), kerningMap(){}
		TextureFont::TextureFont(const std::string &newName):Font(newName), charsMap(), kerningMap(){}
		
		
}