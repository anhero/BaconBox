#include "BaconBox/Display/Text/TextureFont.h"

namespace BaconBox {
		TextureFont::TextureFont():charsMap(), kerningMap(){}
		TextureFont::TextureFont(const std::string &newName):Font(newName), charsMap(), kerningMap(){}


}