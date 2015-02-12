#include "BaconBox/ResourceManager.h"
#include "BaconBox/PlatformFlagger.h"
#include <utility>
#include "BaconBox/Console.h"
#include "BaconBox/Audio/SoundFX.h"
#include "BaconBox/Audio/BackgroundMusic.h"
#include "BaconBox/Audio/SoundInfo.h"
#include "BaconBox/Audio/MusicInfo.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Audio/AudioEngine.h"
#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/MusicEngine.h"
#include "BaconBox/Display/StandardRenderer/Driver/GraphicDriver.h"
#include "BaconBox/Helper/ResourcePathHandler.h"
#include "BaconBox/Display/Color.h"

#include "BaconBox/Display/Text/Font.h"
#include "Display/Text/StandardRenderer/BMFont.h"
#include "BaconBox/Helper/Serialization/XmlSerializer.h"
#include "Symbol.h"
#include "BaconBox/Helper/Parser.h"
#include "BaconBox/ColorMatrix.h"

#if defined(BB_FLASH_PLATFORM)
#include "BaconBox/Audio/Flash/FlashSoundEngine.h"
#include "BaconBox/Audio/Flash/FlashMusicEngine.h"

#endif

#if ! defined(BB_FLASH_PLATFORM)
	//For LibPNG
	#include <stdio.h>
	#include <stdlib.h>
	#include <png.h>
	#define PNG_HEADER_SIZE 8
#endif 

namespace BaconBox {
	std::map<std::string, SoundInfo *> ResourceManager::sounds = std::map<std::string, SoundInfo *>();
	std::map<std::string, MusicInfo *> ResourceManager::musics = std::map<std::string, MusicInfo *>();
	std::map<std::string, std::map<int, Font *> > ResourceManager::fonts = std::map<std::string, std::map<int, Font *> >();
	std::map<std::string, Symbol *> ResourceManager::symbols = std::map<std::string, Symbol *>();


#if ! defined(BB_FLASH_PLATFORM)
	std::map<std::string, TextureInformation *> ResourceManager::textures = std::map<std::string, TextureInformation *>();
	std::map<std::string, SubTextureInfo *> ResourceManager::subTextures = std::map<std::string, SubTextureInfo *>();

	SubTextureInfo *ResourceManager::addSubTexture(const std::string &key, SubTextureInfo *subTextureInfo, bool overwrite) {
		SubTextureInfo *subTexInfo = NULL;
		

		// We check if there is already a texture with this name.
		if (subTextures.find(key) != subTextures.end()) {
			// We check if we overwrite the existing texture or not.
			if (overwrite) {
				// We free the allocated memory.
				subTexInfo = subTextures[key];

				if (subTexInfo) {
					delete subTexInfo;
				}

				// We load the new texture.
				 
				subTextures[key] = subTexInfo = subTextureInfo;
				Console::println("Overwrote the existing subtexture named " + key + ".");

			} else {
				Console::println("Can't load texture with key: " + key +
				                 " texture is already loaded");
				subTexInfo = subTextures[key];
			}

		} else {
			subTexInfo = subTextureInfo;
			// We load the new texture and add it to the map.
			subTextures.insert(std::pair<std::string, SubTextureInfo *>(key, subTextureInfo));
		}

		return subTexInfo;
	}
	
	
	bool ResourceManager::isLoadedTexture(const std::string & key){
		std::map<std::string, TextureInformation *>::iterator found  = textures.find(key);
		if (found != textures.end()) {
			return found->second->isLoaded();
		}
		else{
			return false;
		}
	}

	
	TextureInformation * ResourceManager::createRenderTexture(const std::string &key,
															  unsigned int width,
															  unsigned int height,
															  ColorFormat::type colorFormat,
															  bool overwrite){
		PixMap aPixmap(NULL, width, height, colorFormat);
		return loadTexture(&aPixmap);
	}
	
	
	TextureInformation * ResourceManager::loadTexture(PixMap *aPixmap, TextureInformation * texture){
		return GraphicDriver::getInstance().loadTexture(aPixmap, texture);
	}

	TextureInformation *ResourceManager::loadTexture(TextureInformation * texture){
		if (!texture->isLoaded()) {
			PixMap * pixmap = loadPixMap(texture->path, texture->colorFormat);
			loadTexture(pixmap, texture);
			delete pixmap;
			
		}
		else{
			Console::error("Trying to load a loaded texture with key : " + texture->key);
		}
		SubTextureInfo * subTex =  new SubTextureInfo();
		subTex->size.x = texture->imageWidth;
		subTex->size.y = texture->imageHeight;
		subTex->textureInfo = texture;
		addSubTexture(texture->key, subTex);
		return texture;
	}
	
	TextureInformation *ResourceManager::loadTexture(const std::string &key){
		std::map<std::string, TextureInformation *>::iterator found  = textures.find(key);
		if (found != textures.end()) {
			return loadTexture(found->second);
		}
		
		Console::error("Trying to load unregistered texture with key : " + key);
		return NULL;
	}

	
	TextureInformation * ResourceManager::registerTexture(const std::string &key,
										 const std::string &filePath,
										 ColorFormat::type colorFormat){
		if (textures.find(key) == textures.end()) {
			TextureInformation * textureInfo = new TextureInformation();
			textures[key] = textureInfo;
			textureInfo->key = key;
			textureInfo->path = filePath;
			textureInfo->colorFormat = colorFormat;
			
			return textureInfo;
		}
		
		Console::error("Trying to register texture with existing key : " + key);
		return NULL;
	}
	
	TextureInformation * ResourceManager::registerTextureRelativePath(const std::string &key,
														  const std::string &filePath,
														  ColorFormat::type colorFormat){
		return registerTexture(key,  ResourcePathHandler::getResourcePathFor(filePath), colorFormat);
	}
	
	
	TextureInformation *ResourceManager::loadTexture(const std::string &key,
									const std::string &filePath,
									ColorFormat::type colorFormat){
		TextureInformation* texture = registerTexture(key, filePath, colorFormat);
		return loadTexture(texture);
	}
	
	TextureInformation *ResourceManager::loadTextureRelativePath(const std::string &key,
													 const std::string &filePath,
													 ColorFormat::type colorFormat){
		return loadTexture(key, ResourcePathHandler::getResourcePathFor(filePath), colorFormat);
	}

		TextureInformation *ResourceManager::getTexture(const std::string &key) {
		std::map<std::string, TextureInformation *>::iterator itr = textures.find(key);
		return (itr != textures.end()) ? (itr->second) : (NULL);
	}



	void ResourceManager::removeTexture(const std::string &key) {
		unloadTexture(key);
		textures.erase(key);
	}

	void ResourceManager::unloadTexture(const std::string &key) {
		std::map<std::string, TextureInformation *>::iterator i = textures.find(key);
		TextureInformation *textInfo = i->second;
		GraphicDriver::getInstance().getInstance().deleteTexture(textInfo);
		textInfo->textureId = -1;
	}



	void ResourceManager::loadFlashExporterXML(const std::string &xmlPath) {

		rapidxml::xml_document<> doc;
		
		// We read the document from the stream.
		rapidxml::file<> inputXml(xmlPath.c_str());
		
		doc.parse<0>(inputXml.data());
		rapidxml::xml_node<> *root = doc.first_node();
		
		std::string dirPath = ResourcePathHandler::getPathFromFilename(xmlPath);

		loadFlashExporterTextures(root->first_node("Texture"), dirPath);
		loadFlashExporterSymbols(root->first_node("Symbols"));
	}
	
	
	void ResourceManager::loadFlashExporterTextures(rapidxml::xml_node<> *node, const std::string &dirPath) {
		std::string textureName = node->first_attribute("name")->value();
		rapidxml::xml_attribute<> * textureFormat  = node->first_attribute("textureFormat");
		ColorFormat::type colorFormat = ColorFormat::RGBA;
		if(textureFormat){
			colorFormat = ColorFormat::colorFormatFromString(textureFormat->value());
		}
		
		
		TextureInformation * textureInfo = registerTexture(textureName, dirPath + "/" + node->first_attribute("path")->value(), colorFormat);
		rapidxml::xml_attribute<> * scale  = node->first_attribute("scale");

		float textureScale = 1;
		
		if(scale) textureScale = Parser::stringToDouble(scale->value());
		
						
		for (rapidxml::xml_node<> *subTextNode = node->first_node("SubTexture"); subTextNode; subTextNode = subTextNode->next_sibling()){
			std::string name = subTextNode->first_attribute("name")->value();
			Symbol *symbol = new Symbol();
			symbol->isTexture = true;
			symbol->key = name;
			symbol->textureKey = textureName;
			Vector2 registrationPoint;
			symbol->subTex = addSubTexture(name, new SubTextureInfo());
			
			symbol->subTex->position = Vector2(Parser::stringToDouble(subTextNode->first_attribute("x")->value()), Parser::stringToDouble(subTextNode->first_attribute("y")->value()));
			symbol->subTex->size = Vector2(Parser::stringToDouble(subTextNode->first_attribute("width")->value()), Parser::stringToDouble(subTextNode->first_attribute("height")->value()));
			
			symbol->subTex->textureInfo = textureInfo;

			symbol->blend = Parser::stringToBool(subTextNode->first_attribute("blend")->value());
			
			symbol->scale = textureScale;
			
			
			registrationPoint.x = Parser::stringToDouble(subTextNode->first_attribute("registrationPointX")->value());
			registrationPoint.y = Parser::stringToDouble(subTextNode->first_attribute("registrationPointY")->value());
			
			symbol->registrationPoint = registrationPoint;
			symbols[name] = symbol;
		}
		
}


	void ResourceManager::loadFlashExporterSymbols(rapidxml::xml_node<> *node) {

		rapidxml::xml_attribute<> * found;
		for (rapidxml::xml_node<> *symbolNode = node->first_node("Symbol"); symbolNode; symbolNode = symbolNode->next_sibling()){
				Symbol *symbol = new Symbol();

				found = symbolNode->first_attribute("className");
				if (found) {
					symbol->key = found->value();
				}
				
				found = symbolNode->first_attribute("textfield");
				if (found) {
					symbol->isTextField = Parser::stringToBool(found->value());
				}

				if(symbol->isTextField) {
					found = symbolNode->first_attribute("text");
					if (found) {
						symbol->text = found->value();
					}
					
					found = symbolNode->first_attribute("fontSize");
					if (found) {
						symbol->fontSize = Parser::stringToInt(found->value());
					}

					found = symbolNode->first_attribute("color");
					if (found){
	                    std::vector<int> temp;
	                   Parser::parseStringArray<int>(found->value(), temp);
	                    symbol->color = Color(temp[0], temp[1], temp[2]);
					}



					found = symbolNode->first_attribute("font");

					if (found) {
						symbol->font = found->value();
					}

					symbol->frameCount  = 1;

					std::string alignment;

					found = symbolNode->first_attribute("alignment");
					if (found) {
						alignment = found->value();
					}

					if(alignment == "left"){
						symbol->alignment = TextAlignment::LEFT;
					}
					else if(alignment == "center"){
						symbol->alignment = TextAlignment::CENTER;
					}
					else if(alignment == "right"){
						symbol->alignment = TextAlignment::RIGHT;
					}

					
					found = symbolNode->first_attribute("width");
					if (found) {
						symbol->textFieldWidth = Parser::stringToInt(found->value());
					}
					
					
					found = symbolNode->first_attribute("height");
					if (found) {
						symbol->textFieldHeight = Parser::stringToInt(found->value());
					}

				} else {
					found = symbolNode->first_attribute("frameCount");
					if (found) {
						symbol->frameCount = Parser::stringToInt(found->value());
					}
					found = symbolNode->first_attribute("autoPlay");
					symbol->autoPlay = false;
					if (found) {
						symbol->autoPlay = Parser::stringToBool(found->value());
					}

				}

				symbols[symbol->key] = symbol;
		}

		for (rapidxml::xml_node<> *symbolNode = node->first_node("Symbol"); symbolNode; symbolNode = symbolNode->next_sibling()){
	
			found = symbolNode->first_attribute("className");
			Symbol *parent = symbols[found->value()];
			
			for (rapidxml::xml_node<> *labelNode = symbolNode->first_node("label"); labelNode; labelNode = labelNode->next_sibling("label")){

                            int startFrame = 0;
                            int endframe = -1;
                            std::string name;

							found = labelNode->first_attribute("name");
                            if (found) {
                                name = found->value();
                            }
				
							found = labelNode->first_attribute("startFrame");
							if (found) {
								startFrame = Parser::stringToInt(found->value());
							}
				
							found = labelNode->first_attribute("endFrame");
							if (found) {
								endframe = Parser::stringToInt(found->value());
							}

                
								parent->label[name] = std::pair<int, int>(startFrame, endframe);
			}

			
			std::map<std::string, Symbol::Part*> children;
			int frameIndex = 0;

			for (rapidxml::xml_node<> *frameNode = symbolNode->first_node("Frame"); frameNode; frameNode = frameNode->next_sibling()){

				int index = 0;

				for (rapidxml::xml_node<> *childNode = frameNode->first_node("Child"); childNode; childNode = childNode->next_sibling()){
					std::string name;

					found = childNode->first_attribute("name");

					if (found) {
						name = found->value();
					}

					std::string className;

					found = childNode->first_attribute("className");

					if (found) {
						className = found->value();
					}

					Symbol::Part *part;
					std::map<std::string, Symbol::Part*>::iterator i = children.find(name);
					if (i == children.end()) {
						part = children[name] = new Symbol::Part();
						part->name = name;
						part->symbol = symbols[className];
						if(! part->symbol){
							Console__error("Trying to add a NULL symbol part with key " << className << " to " << parent->key);
						}
					}
					else{
						part = i->second;
					}

					part->indexByFrame.insert(std::pair<int, int>(frameIndex, index));

					Matrix2D matrix;
					found = childNode->first_attribute("a");
					if (found) {
						matrix.a = Parser::stringToDouble(found->value());
					}
			
					
					found = childNode->first_attribute("b");
					if (found) {
						matrix.b = Parser::stringToDouble(found->value());
					}
					found = childNode->first_attribute("c");
					if (found) {
						matrix.c = Parser::stringToDouble(found->value());
					}
					found = childNode->first_attribute("d");
					if (found) {
						matrix.d = Parser::stringToDouble(found->value());
					}
					found = childNode->first_attribute("tx");
					if (found) {
						matrix.tx = Parser::stringToDouble(found->value());
					}
					found = childNode->first_attribute("ty");
					if (found) {
						matrix.ty = Parser::stringToDouble(found->value());
					}

					
					part->matrices.insert(std::pair<int, Matrix2D>(frameIndex, matrix));

					ColorMatrix colorMatrix;
					found = childNode->first_attribute("colorTransform");
					if (found) {
                        std::vector<float> temp;
                       Parser::parseStringArray<float>(found->value(), temp);
                       float divider = 1.0f / 255.0f;
                        colorMatrix.colorMultiplier.setRGBA(temp[0], temp[2], temp[4], temp[6]);
                        colorMatrix.colorOffset.setRGBA(temp[1] * divider, temp[3] * divider, temp[5] * divider, temp[7] * divider);
                    }
					part->colorMatrices.insert(std::pair<int, ColorMatrix>(frameIndex, colorMatrix));

					index++;
				}
			
				frameIndex++;
			}

			for(std::map<std::string, Symbol::Part*>::iterator j = children.begin(); j != children.end(); j++){
				parent->parts.push_back(*(j->second));
			}
		}
	}


	void ResourceManager::deleteAllSubTexture() {
		for (std::map<std::string, SubTextureInfo *>::iterator i = subTextures.begin();
		     i != subTextures.end(); ++i) {
			delete i->second;
		}
		
		subTextures.clear();
	}
	
	void ResourceManager::deleteAllTexture() {
		for (std::map<std::string, TextureInformation *>::iterator i = textures.begin();
		     i != textures.end(); ++i) {
			ResourceManager::unloadTexture(i->first);
			delete i->second;
		}
		
		textures.clear();
		ResourceManager::deleteAllSubTexture();
	}

	void ResourceManager::unloadAllTexture() {
		for (std::map<std::string, TextureInformation *>::iterator i = textures.begin();
		     i != textures.end(); ++i) {
			ResourceManager::unloadTexture(i->first);
		}
		
	}
	
	void ResourceManager::unloadAllTextureExcept(const std::set<std::string> exceptions){
		for (std::map<std::string, TextureInformation *>::iterator i = textures.begin();
		     i != textures.end(); ++i) {
			if(exceptions.find(i->first) == exceptions.end())ResourceManager::unloadTexture(i->first);
		}
	}

	PixMap *ResourceManager::loadPixMap(const std::string &filePath, ColorFormat::type colorFormat) {
		PixMap *pixmap = loadPixMapFromPNG(filePath);

		if (pixmap && colorFormat != pixmap->getColorFormat()) {
			pixmap->convertTo(colorFormat);
		}

		return pixmap;
	}

	PixMap *ResourceManager::loadPixMap(const std::string &filePath,
	                                    const Color &transparentColor) {
		PixMap *result = loadPixMap(filePath, ColorFormat::RGBA);

		if (result) {
			result->makeColorTransparent(transparentColor);
		}

		return result;
	}

	void ResourceManager::savePixMap(const BaconBox::PixMap &pixMap,
	                                 const std::string &filePath) {
		savePixMapToPNG(pixMap, filePath);
	}

	PixMap *ResourceManager::loadPixMapFromPNG(const std::string &filePath) {
		FILE *PNG_file = fopen(filePath.c_str(), "rb");

		if (PNG_file == NULL) {
			Console::println("Unable to open this png file : " + filePath);
			return NULL;
		}

		uint8_t PNG_header[PNG_HEADER_SIZE];
		fread(PNG_header, 1, PNG_HEADER_SIZE, PNG_file);

		if (png_sig_cmp(PNG_header, 0, PNG_HEADER_SIZE) != 0) {
			Console::println("Trying to load a non png file as a png file. Path to file :" + filePath);
		}

		png_structp PNG_reader
		    = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if (PNG_reader == NULL) {
			Console::println("Cannot read this png file " + filePath);
		}

		png_infop PNG_info = png_create_info_struct(PNG_reader);

		if (PNG_info == NULL) {
			Console::println("Cannot extract info from this png file : " + filePath);
			png_destroy_read_struct(&PNG_reader, NULL, NULL);
		}

		png_infop PNG_end_info = png_create_info_struct(PNG_reader);

		if (PNG_end_info == NULL) {
			Console::println("Cannot extract end info from this png file : " + filePath);
			png_destroy_read_struct(&PNG_reader, &PNG_info, NULL);
		}

		if (setjmp(png_jmpbuf(PNG_reader))) {
			Console::println("Cannot load this png file " + filePath);
			png_destroy_read_struct(&PNG_reader, &PNG_info, &PNG_end_info);
		}

		png_init_io(PNG_reader, PNG_file);
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

		} else {
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
		fclose(PNG_file);
		PixMap *aPixMap = new PixMap(PNG_image_buffer, width, height);
		return aPixMap;
	}

	void ResourceManager::savePixMapToPNG(const PixMap &pixMap, const std::string &filePath) {
		FILE *fp = fopen(filePath.c_str(), "wb");

		if (fp) {
			png_structp pngPointer = png_create_write_struct(PNG_LIBPNG_VER_STRING,
			                                                 NULL, NULL, NULL);

			if (pngPointer) {
				png_infop infoPointer = png_create_info_struct(pngPointer);

				if (infoPointer) {

					if (!setjmp(png_jmpbuf(pngPointer))) {
						png_init_io(pngPointer, fp);

						if (!setjmp(png_jmpbuf(pngPointer))) {
							png_set_IHDR(pngPointer,
							             infoPointer,
							             pixMap.getWidth(),
							             pixMap.getHeight(),
							             8,
							             ((pixMap.getColorFormat() == ColorFormat::RGBA) ? (PNG_COLOR_TYPE_RGBA) : (PNG_COLOR_TYPE_GRAY)),
							             PNG_INTERLACE_NONE,
							             PNG_COMPRESSION_TYPE_DEFAULT,
							             PNG_FILTER_TYPE_DEFAULT);

							png_write_info(pngPointer, infoPointer);

							if (!setjmp(png_jmpbuf(pngPointer))) {
								png_bytepp rows = new png_bytep[pixMap.getHeight()];
								png_bytep tmpBuffer = const_cast<png_bytep>(pixMap.getBuffer());
								unsigned int nbChannels = (pixMap.getColorFormat() == ColorFormat::RGBA) ? (4) : (1);

								for (unsigned int i = 0; i < pixMap.getHeight(); ++i) {
									rows[i] = tmpBuffer + (i * nbChannels * pixMap.getWidth());
								}

								png_write_image(pngPointer, rows);
								delete [] rows;
								rows = NULL;

								if (!setjmp(png_jmpbuf(pngPointer))) {
									png_write_end(pngPointer, NULL);

								} else {
									Console::println("Error during end of write to PNG file.");
								}

							} else {
								Console::println("Error while writing bytes to PNG file.");
							}

						} else {
							Console::println("Error while writing PNG header.");
						}

					} else {
						Console::println("Error during init_io.");
					}

				} else {
					Console::println("png_create_info_struct failed.");
				}

			} else {
				Console::println("png_create_write_struct failed.");
			}

			fclose(fp);

		} else {
			Console::print("Could not write the PixMap to the PNG file ");
			Console::print(filePath);
			Console::println(".");
		}
	}

	SubTextureInfo *ResourceManager::getSubTexture(const std::string &key, bool loadTextureIfNotLoaded) {
		std::map<std::string, SubTextureInfo *>::iterator itr = subTextures.find(key);
		SubTextureInfo * subTex = (itr != subTextures.end()) ? (itr->second) : (NULL);
		if (!subTex) {
			Console__error("FATAL : Could not find subtexture in getSubTexture for key: `" << key << "`");
		}
		if (loadTextureIfNotLoaded && ! subTex->textureInfo->isLoaded()) {
			loadTexture(subTex->textureInfo);
		}
		return subTex;
	}

	#endif
	
	Symbol *ResourceManager::getSymbol(const std::string &key) {
		std::map<std::string, Symbol *>::iterator itr = symbols.find(key);
		return (itr != symbols.end()) ? (itr->second) : (NULL);
	}

	Symbol *ResourceManager::addSymbol(const std::string &key, Symbol * symbol, bool overwrite){

		
		Symbol * tempSymbol;
		// We check if there is already a texture with this name.
		if (symbols.find(key) != symbols.end()) {
			// We check if we overwrite the existing texture or not.
			if (overwrite) {
				if(symbol == NULL){
					symbol = new Symbol();
					symbol->key = key;
				}
				// We free the allocated memory.
				tempSymbol = symbols[key];

				if (tempSymbol) {
					delete tempSymbol;
				}

				// We load the new texture.
				 
				symbols[key] = tempSymbol = symbol;
				Console::println("Overwrote the existing symbol named " + key + ".");

			} else {
				Console::println("Can't overwrite symbol with key: " + key);
				tempSymbol = symbols[key];
			}

		} else {
			if(symbol == NULL){
				symbol = new Symbol();
				symbol->key = key;
			}
			tempSymbol = symbol;
			// We load the new texture and add it to the map.
			symbols.insert(std::pair<std::string, Symbol *>(key, symbol));
		}

		return tempSymbol;
	}

	

	SoundInfo *ResourceManager::getSound(const std::string &key) {
		std::map<std::string, SoundInfo *>::iterator itr = sounds.find(key);
		return (itr != sounds.end()) ? (itr->second) : (NULL);
	}

	MusicInfo *ResourceManager::getMusic(const std::string &key) {
		std::map<std::string, MusicInfo *>::iterator itr = musics.find(key);
		return (itr != musics.end()) ? (itr->second) : (NULL);
	}

	SoundInfo *ResourceManager::loadSound(const std::string &key,
	                                      const std::string &filePath,
	                                      bool overwrite) {
		SoundInfo *newSnd = NULL;

		if (sounds.find(key) != sounds.end()) {
			if (overwrite) {
				// We delete the existing sound effect.
				newSnd = sounds[key];

				if (newSnd) {
					delete newSnd;
				}

				// We load the sound effect and we overwrite the existing sound
				// effect.
				newSnd = sounds[key] = AudioEngine::getSoundEngine().loadSound(filePath);
				Console::println("Overwrote the existing sound effect named " + key +
				                 ".");

			} else {
				Console::println("Couldn't load the sound effect named " + key +
				                 " found at " + filePath +
				                 " because a sound with that name already exists.");
				newSnd = sounds[key];
			}

		} else {
			// We load the sound effect.
			newSnd = AudioEngine::getSoundEngine().loadSound(filePath);

			// If it was loaded correctly.
			if (newSnd) {
				// We insert it into the map of sound effects with its
				// corresponding key.
				sounds.insert(std::pair<std::string, SoundInfo *>(key, newSnd));
			}
		}

		return newSnd;
	}


	MusicInfo *ResourceManager::loadMusicFromBundle(const std::string &key,
	                                                const std::string &bundleKey,
	                                                bool overwrite) {
#if defined(BB_FLASH_PLATFORM)
		MusicInfo *newBgm = NULL;

		if (musics.find(key) != musics.end()) {
			if (overwrite) {
				// We delete the existing music.
				newBgm = musics[key];

				if (newBgm) {
					delete newBgm;
				}

				// We load the music and we overwrite the existing music.
				newBgm = musics[key] = reinterpret_cast<FlashMusicEngine *>(&AudioEngine::getMusicEngine())->loadMusicFromBundle(bundleKey);
				Console::println("Overwrote the existing music named " + key +
				                 ".");

			} else {
				Console::println("Couldn't load the music named " + key +
				                 " with bundle key " + bundleKey +
				                 " because a music with that name already exists.");
				newBgm = musics[key];
			}

		} else {
			// We load the music.
			newBgm = reinterpret_cast<FlashMusicEngine *>(&AudioEngine::getMusicEngine())->loadMusicFromBundle(bundleKey);

			// If it was loaded correctly.
			if (newBgm) {
				// We insert it into the map of musics with its corresponding
				// key.
				musics.insert(std::pair<std::string, MusicInfo *>(key, newBgm));
			}
		}

		return newBgm;
#else
		return NULL;
#endif
	}



	SoundInfo *ResourceManager::loadSoundFromBundle(const std::string &key,
	                                                const std::string &bundleKey,
	                                                bool overwrite) {

#if defined(BB_FLASH_PLATFORM)
		SoundInfo *newSnd = NULL;

		if (sounds.find(key) != sounds.end()) {
			if (overwrite) {
				// We delete the existing sound effect.
				newSnd = sounds[key];

				if (newSnd) {
					delete newSnd;
				}

				// We load the sound effect and we overwrite the existing sound
				// effect.
				newSnd = sounds[key] = reinterpret_cast<FlashSoundEngine *>(&FlashSoundEngine::getSoundEngine())->loadSoundFromBundle(bundleKey);
				Console::println("Overwrote the existing sound effect named " + key +
				                 ".");

			} else {
				Console::println("Couldn't load the sound effect named " + key +
				                 " with bundle key " + bundleKey +
				                 " because a sound with that name already exists.");
				newSnd = sounds[key];
			}

		} else {
			// We load the sound effect.
			newSnd = reinterpret_cast<FlashSoundEngine *>(&FlashSoundEngine::getSoundEngine())->loadSoundFromBundle(bundleKey);

			// If it was loaded correctly.
			if (newSnd) {
				// We insert it into the map of sound effects with its
				// corresponding key.
				sounds.insert(std::pair<std::string, SoundInfo *>(key, newSnd));
			}
		}

		return newSnd;
#else
		return NULL;
#endif
	}

	SoundInfo *ResourceManager::loadSoundRelativePath(const std::string &key,
	                                                  const std::string &relativePath,
	                                                  bool overwrite) {
		return loadSound(key, ResourcePathHandler::getResourcePathFor(relativePath),
		                 overwrite);
	}

	SoundInfo *ResourceManager::loadSound(const SoundParameters &params,
	                                      bool overwrite) {
		SoundInfo *newSnd = NULL;

		if (sounds.find(params.name) != sounds.end()) {
			if (overwrite) {
				// We delete the existing sound effect.
				newSnd = sounds[params.name];

				if (newSnd) {
					delete newSnd;
				}

				// We load the sound effect and we overwrite the existing sound
				// effect.
				newSnd = sounds[params.name] = AudioEngine::getSoundEngine().loadSound(params);
				Console::println("Overwrote the existing sound effect named " +
				                 params.name + ".");

			} else {
				Console::println("Couldn't load the sound effect named " + params.name +
				                 " because a sound with that name already exists.");
				newSnd = sounds[params.name];
			}

		} else {
			// We load the sound effect.
			newSnd = AudioEngine::getSoundEngine().loadSound(params);

			// If it was loaded correctly.
			if (newSnd) {
				// We insert it into the map of sound effects with its
				// corresponding key.
				sounds.insert(std::pair<std::string, SoundInfo *>(params.name,
				                                                  newSnd));
			}
		}

		return newSnd;
	}

	MusicInfo *ResourceManager::loadMusic(const std::string &key,
	                                      const std::string &filePath,
	                                      bool overwrite) {
		MusicInfo *newBgm = NULL;

		if (musics.find(key) != musics.end()) {
			if (overwrite) {
				// We delete the existing music.
				newBgm = musics[key];

				if (newBgm) {
					delete newBgm;
				}

				// We load the music and we overwrite the existing music.
				newBgm = musics[key] = AudioEngine::getMusicEngine().loadMusic(filePath);
				Console::println("Overwrote the existing music named " + key +
				                 ".");

			} else {
				Console::println("Couldn't load the music named " + key +
				                 " found at " + filePath +
				                 " because a music with that name already exists.");
				newBgm = musics[key];
			}

		} else {
			// We load the music.
			newBgm = AudioEngine::getMusicEngine().loadMusic(filePath);

			// If it was loaded correctly.
			if (newBgm) {
				// We insert it into the map of musics with its corresponding
				// key.
				musics.insert(std::pair<std::string, MusicInfo *>(key, newBgm));
			}
		}

		return newBgm;
	}

	MusicInfo *ResourceManager::loadMusicRelativePath(const std::string &key,
	                                                  const std::string &relativePath,
	                                                  bool overwrite) {
		return loadMusic(key, ResourcePathHandler::getResourcePathFor(relativePath),
		                 overwrite);
	}

	MusicInfo *ResourceManager::loadMusic(const MusicParameters &params,
	                                      bool overwrite) {
		MusicInfo *newBgm = NULL;

		if (musics.find(params.name) != musics.end()) {
			if (overwrite) {
				// We delete the existing music.
				newBgm = musics[params.name];

				if (newBgm) {
					delete newBgm;
				}

				// We load the music and we overwrite the existing music.
				newBgm = musics[params.name] = AudioEngine::getMusicEngine().loadMusic(params);
				Console::println("Overwrote the existing music named " + params.name + ".");

			} else {
				Console::println("Couldn't load the music named " + params.name +
				                 " because a music with that name already exists.");
				newBgm = musics[params.name];
			}

		} else {
			// We load the music.
			newBgm = AudioEngine::getMusicEngine().loadMusic(params);

			// If it was loaded correctly.
			if (newBgm) {
				// We insert it into the map of musics with its corresponding
				// key.
				musics.insert(std::pair<std::string, MusicInfo *>(params.name, newBgm));
			}
		}

		return newBgm;
	}

	

	void ResourceManager::removeSound(const std::string &key) {
		// We find the sound effect.
		std::map<std::string, SoundInfo *>::iterator snd = sounds.find(key);

		// We check if the sound effect asked exists and we ask the sound engine to
		// unload the data.
		if (snd != sounds.end()) {
			if (AudioEngine::getSoundEngine().unloadSound(snd->second)) {
				// We delete it.
				delete(snd->second);
				// We remove it from the map.
				sounds.erase(snd);

			} else {
				Console::println("The sound effect named " + key + " could not be removed because the audio engine failed to unload it.");
			}

		} else {
			Console::println("The sound effect named " + key + " could not be removed because it doesn't exist.");
		}
	}

	void ResourceManager::removeMusic(const std::string &key) {
		// We find the music.
		std::map<std::string, MusicInfo *>::iterator music = musics.find(key);

		// We check if the music asked exists and we ask the music engine to
		// unload the data.
		if (music != musics.end()) {
			if (AudioEngine::getMusicEngine().unloadMusic(music->second)) {
				// We delete it.
				delete(music->second);
				// We remove it from the map.
				musics.erase(music);

			} else {
				Console::println("The music named " + key + " could not be removed because the audio engine failed to unload it.");
			}

		} else {
			Console::println("The music named " + key + " could not be removed because it doesn't exist.");
		}
	}
	





	Font *ResourceManager::initFontFromPath(const std::string &key,
	                                        const std::string &path) {

		if (path.substr(path.find_last_of(".") + 1) == "fnt") {
			return initFontFromPathAndFormat(key, path, FontFormat::BMFONT);
		}

		Console__error("Error initializing font " << key);
		return NULL;
	}
	
	
	void ResourceManager::addFontAlias(const std::string &key, const std::string &existingKey){
		fonts[key] = fonts[existingKey];
	}


	Font *ResourceManager::initFontFromPathAndFormat(const std::string &key,
	                                                 const std::string &path, const FontFormat &format) {
#if ! defined (BB_FLASH_PLATFORM)

		if (format == FontFormat::BMFONT) {
			BMFont *font = new BMFont(key);
			font->format = format;
			font->loadFontFile(path);
			return font;

		}

#endif
		Console__error("No font fit the given format");
		return NULL;
	}


	Font *ResourceManager::loadFont(const std::string &key, const std::string &path, int fontSize) {
		Font *aFont = NULL;
	
			aFont = initFontFromPath(key, path);
			fonts[key][fontSize] = aFont;

		return aFont;
	}

	Font *ResourceManager::loadFontRelativePath(const std::string &key,
	                                            const std::string &relativePath, int fontSize) {
		return loadFont(key, ResourcePathHandler::getResourcePathFor(relativePath), fontSize);
	}

	Font *ResourceManager::getFont(const std::string &key, int fontSize) {
		std::map<std::string, std::map<int, Font *> >::iterator itr = fonts.find(key);
		std::map<int, Font *>::iterator i;
		for (i = itr->second.begin(); i != itr->second.end(); i++) {
			if(i->first >= fontSize)break;
		}
		
		return (i  != itr->second.end()) ? (i->second) : (NULL);
	}

	void ResourceManager::removeFont(const std::string &key, int fontSize) {
		std::map<std::string, std::map<int, Font *> >::iterator itr = fonts.find(key);
		std::map<int, Font *>::iterator i;
		for (i = itr->second.begin(); i != itr->second.end(); i++) {
			if(fontSize == i->first || fontSize < 0) delete i->second;
				if(fontSize == i->first){
					itr->second.erase(i);
				}
		}
		
		if (fontSize < 0) {
			fonts.erase(itr);
		}
	}
	
	
	
	void ResourceManager::deleteAllSymbol() {
		for (std::map<std::string, Symbol *> ::iterator i = symbols.begin();
		     i != symbols.end(); ++i) {
			delete i->second;
		}
		
		symbols.clear();
	}
	
	
	void ResourceManager::deleteAll() {
		
		ResourceManager::deleteAllSymbol();
		
		#if ! defined(BB_FLASH_PLATFORM)
		// We unload the textures.
		ResourceManager::deleteAllTexture();
		#endif
		// We unload the sound effects.
		for (std::map<std::string, SoundInfo *>::iterator i = sounds.begin();
		     i != sounds.end(); ++i) {
			AudioEngine::getSoundEngine().unloadSound(i->second);
			delete i->second;
		}

		sounds.clear();

		// We unload the musics.
		for (std::map<std::string, MusicInfo *>::iterator i = musics.begin();
		     i != musics.end(); ++i) {
			AudioEngine::getMusicEngine().unloadMusic(i->second);
			delete i->second;
		}

		musics.clear();

		// We unload the fonts.
	
		
		for(std::map<std::string, std::map<int, Font *> >::iterator itr  = fonts.begin();
		itr != fonts.end(); ++itr) {
		std::map<int, Font *>::iterator i;
		for (i = itr->second.begin(); i != itr->second.end(); i++) {
			delete i->second;
		}
		}
		
		fonts.clear();
	}

	
}
