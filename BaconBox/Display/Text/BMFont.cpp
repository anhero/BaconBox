#include <fstream>

#include "BaconBox/Display/Text/BMFont.h"
#include "BaconBox/Console.h"
#include <fstream>
#include "BaconBox/Helper/Serialization/XmlSerializer.h"
#include "BaconBox/Helper/ResourcePathHandler.h"
#include "BaconBox/ResourceManager.h"
namespace BaconBox {
		BMFont::BMFont(){}
		BMFont::BMFont(const std::string &newName):TextureFont(newName){}
		
		
		
		int BMFont::getKerning(Char32 leftUnicodeValue, Char32 rightUnicodeValue){
		    
		}

		
	
		const TextureGlyphInformation * BMFont::getGlyphInformation(Char32 unicodeValue){
		    
		}

	
		void BMFont::setPixelSize(int pixelSize){
		    Console__error("You can't set the pixel size on this font: " << name << ". BMFont are prerendered.")
		}
		
		void BMFont::loadFontFile(const std::string &filename){
		    std::fstream f;
		     f.open(filename.c_str());
		     char firstChar;
		     f.get(firstChar);
		     
		     f.seekg(0, std::ios::beg);
		     
		     if(firstChar == 'i'){
			//Text
		     }
		     else if(firstChar == '<'){
			Value font;
			XmlSerializer xmlReader;
			if(xmlReader.readFromStream(f, font)){
			     std::string path = ResourcePathHandler::getPathFromFilename(filename);

			     //if there is more than one texture for the font.
			    Array pages = font["pages"]["page"].getArray();
			  for(Array::iterator i = pages.begin(); i != pages.end(); i++){
			      std::string textureFilename = (*i)["file"].getString();
			      PV(textureFilename);
			      textureFilename.insert(0, 1, '/');
				textureFilename.insert(0, path);
				PV(textureFilename);
				BaconBox::ResourceManager::loadTexture("test.nope", textureFilename);
					
			  } 
			   
			    
			}
			else{
			    Console__error("Failed to load a fond : " << filename);
			}
		     }
		     else {
			 //Binary
		     }
		     
		     f.close();

		 
		}


}