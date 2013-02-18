#include "BaconBox/Display/Text/Font.h"
#include "BaconBox/Display/Text/TextEntity.h"
namespace BaconBox {
		Font::Font(): format(FontFormat::NONE){}
		Font::Font(const std::string &newName):name(newName), format(FontFormat::NONE){}
		void Font::setPixelSize(int pixelSize){
		    this->pixelSize = pixelSize;
		}
		
		const std::string &Font::getName() const{
		    return name;
		}
		
		void Font::setName(const std::string &newName){
		    name = newName;
		}
		
    		int Font::getPixelSize(){
		    return pixelSize;
		}
		TextEntity * Font::getTextEntity(){
		    return new TextEntity(this);
		}

		FontFormat Font::getFormat(){
		    return format;
		}

}