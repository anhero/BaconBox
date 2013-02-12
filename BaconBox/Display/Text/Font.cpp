#include "BaconBox/Display/Text/Font.h"

namespace BaconBox {
		Font::Font(){}
		Font::Font(const std::string &newName):name(newName){}
		void Font::setPixelSize(int pixelSize){
		    this->pixelSize = pixelSize;
		}
    		int Font::getPixelSize(){
		    return pixelSize;
		}

}