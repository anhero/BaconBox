#include "BaconBox/ResourceManager.h"

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
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/Helper/ResourcePathHandler.h"
#include "BaconBox/Display/Color.h"

#include "BaconBox/Display/Text/Font.h"
#include "Display/Text/BMFont.h"
#include "BaconBox/Helper/Serialization/XmlSerializer.h"
#include "Symbol.h"

#if defined(BB_FLASH_PLATEFORM)
#include "BaconBox/Audio/Flash/FlashSoundEngine.h"
#include "BaconBox/Audio/Flash/FlashMusicEngine.h"

#endif


//For LibPNG
#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#define PNG_HEADER_SIZE 8

namespace BaconBox {
	std::map<std::string, TextureInformation *> ResourceManager::textures = std::map<std::string, TextureInformation *>();
	std::map<std::string, SubTextureInfo *> ResourceManager::subTextures = std::map<std::string, SubTextureInfo *>();
	std::map<std::string, SoundInfo *> ResourceManager::sounds = std::map<std::string, SoundInfo *>();
	std::map<std::string, MusicInfo *> ResourceManager::musics = std::map<std::string, MusicInfo *>();
	std::map<std::string, Font *> ResourceManager::fonts = std::map<std::string, Font *>();
	std::map<std::string, Symbol*> ResourceManager::symbols = std::map<std::string, Symbol*>();
	
	SubTextureInfo *ResourceManager::addSubTexture(const std::string &key, SubTextureInfo *subTextureInfo, bool overwrite){
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
				subTextures[key] = subTextureInfo;
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
	
	    TextureInformation *ResourceManager::addTextureWithPath(const std::string &key, PixMap *aPixmap, const std::string & path, bool overwrite){
		    TextureInformation *texInfo = addTexture(key, aPixmap,overwrite);
		    texInfo->path = path;
		    return texInfo;
	    }


	TextureInformation *ResourceManager::addTexture(const std::string &key, PixMap *aPixmap,
	                                                bool overwrite) {
		TextureInformation *texInfo = NULL;
		if(overwrite || !isExistingTexture(key)){
		    		    texInfo = addTextureInfo(key, GraphicDriver::getInstance().loadTexture(aPixmap), overwrite);

		}else {
		    Console::println("Can't load texture with key: " + key +
				                 " texture is already loaded");
		} 	
		return texInfo;
	}
	bool ResourceManager::isExistingTexture(const std::string & key){
	    return textures.find(key) != textures.end() && textures[key] == NULL;
	}
	
	
	TextureInformation *ResourceManager::addTextureInfo(const std::string &key, TextureInformation *textureInfo,
	                                                bool overwrite) {
		TextureInformation *texInfo = NULL;

		// We check if there is already a texture with this name.
		if (isExistingTexture(key)) {
		    	texInfo = textures[key];
			// We check if we overwrite the existing texture or not.
			if (overwrite || textures[key] == NULL) {
				// We free the allocated memory.

				if (texInfo) {
					delete texInfo;
				}
				texInfo = textureInfo;
				ResourceManager::addSubTexture(key, new SubTextureInfo(texInfo, Vector2(),Vector2(texInfo->imageWidth, texInfo->imageHeight)), overwrite);
				Console::println("Overwrote the existing texture named " + key + ".");
			} else {
				Console::println("Can't load texture with key: " + key +
				                 " texture is already loaded");
				texInfo = textures[key];
			}

		} else {
			// We load the new texture and add it to the map.
			texInfo = textureInfo;
			textures.insert(std::pair<std::string, TextureInformation *>(key, texInfo));
			ResourceManager::addSubTexture(key, new SubTextureInfo(texInfo, Vector2(),Vector2(texInfo->imageWidth, texInfo->imageHeight)));
		}
		
		
		return texInfo;
	}
			
	
	TextureInformation *ResourceManager::loadTexture(const std::string &key){
	    TextureInformation * texture = textures[key];
	    textures[key] = NULL;
	    loadTexture(key, texture->path, texture->colorFormat, true);
	}

	void ResourceManager::registerTexture(const std::string &key,
	                                                 const std::string &filePath,
	                                                 ColorFormat colorFormat,
	                                                 bool overwrite) {
	    TextureInformation * textureInfo = new TextureInformation();
	    textureInfo->path = filePath;
	    textureInfo->colorFormat = colorFormat;
	    addTextureInfo(key, textureInfo, overwrite);
	}

	TextureInformation *ResourceManager::loadTexture(const std::string &key,
	                                                 const std::string &filePath,
	                                                 ColorFormat colorFormat,
	                                                 bool overwrite) {
		PixMap *pixMap = loadPixMap(filePath, colorFormat);

		if (pixMap) {
			TextureInformation *result = addTextureWithPath(key, pixMap, filePath, overwrite);
			delete pixMap;
			return result;

		} else {
			return NULL;
		}
	}

	TextureInformation *ResourceManager::loadTextureWithColorKey(const std::string &key,
	                                                             const std::string &filePath,
	                                                             const Color &transparentColor,
	                                                             bool overwrite) {
		PixMap *pixMap = loadPixMap(filePath, transparentColor);

		if (pixMap) {
			TextureInformation *result = addTextureWithPath(key, pixMap, filePath, overwrite);
			delete pixMap;
			return result;

		} else {
			return NULL;
		}
	}

	TextureInformation *ResourceManager::loadTextureRelativePath(const std::string &key,
	                                                             const std::string &relativePath,
	                                                             ColorFormat colorFormat,
	                                                             bool overwrite) {
		return loadTexture(key,
		                   ResourcePathHandler::getResourcePathFor(relativePath),
		                   colorFormat, overwrite);
	}

	TextureInformation *ResourceManager::loadTextureRelativePathWithColorKey(const std::string &key,
	                                                                         const std::string &relativePath,
	                                                                         const Color &transparentColor,
	                                                                         bool overwrite) {
		return loadTextureWithColorKey(key,
		                               ResourcePathHandler::getResourcePathFor(relativePath),
		                               transparentColor, overwrite);
	}

	Symbol *ResourceManager::getSymbol(const std::string &key){
	    std::map<std::string, Symbol *>::iterator itr = symbols.find(key);
		return (itr != symbols.end()) ? (itr->second) : (NULL);
	}
	SubTextureInfo *ResourceManager::getSubTexture(const std::string &key){
	    std::map<std::string, SubTextureInfo *>::iterator itr = subTextures.find(key);
		return (itr != subTextures.end()) ? (itr->second) : (NULL);
	}

	TextureInformation *ResourceManager::getTexture(const std::string &key) {
		std::map<std::string, TextureInformation *>::iterator itr = textures.find(key);
		return (itr != textures.end()) ? (itr->second) : (NULL);
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
		                            bool overwrite){
#if defined(BB_FLASH_PLATEFORM)
MusicInfo *newBgm = NULL;

		if (musics.find(key) != musics.end()) {
			if (overwrite) {
				// We delete the existing music.
				newBgm = musics[key];

				if (newBgm) {
					delete newBgm;
				}

				// We load the music and we overwrite the existing music.
				newBgm = musics[key] = reinterpret_cast<FlashMusicEngine*>(&AudioEngine::getMusicEngine())->loadMusicFromBundle(bundleKey);
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
			newBgm = reinterpret_cast<FlashMusicEngine*>(&AudioEngine::getMusicEngine())->loadMusicFromBundle(bundleKey);

			// If it was loaded correctly.
			if (newBgm) {
				// We insert it into the map of musics with its corresponding
				// key.
				musics.insert(std::pair<std::string, MusicInfo *>(key, newBgm));
			}
		}

		return newBgm;
#endif	    
	}
	
	
	
SoundInfo * ResourceManager::loadSoundFromBundle(const std::string &key,
		                            const std::string &bundleKey,
		                            bool overwrite){
	    
#if defined(BB_FLASH_PLATEFORM)
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
				newSnd = sounds[key] = reinterpret_cast<FlashSoundEngine*>(&FlashSoundEngine::getSoundEngine())->loadSoundFromBundle(bundleKey);
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
			newSnd = reinterpret_cast<FlashSoundEngine*>(&FlashSoundEngine::getSoundEngine())->loadSoundFromBundle(bundleKey);

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
    
    void ResourceManager::removeTexture(const std::string &key){
        unloadTexture(key);
        textures.erase(key);
    }
    
    void ResourceManager::unloadTexture(const std::string &key){
	TextureInformation * textInfo = textures[key];
        GraphicDriver::getInstance().getInstance().deleteTexture(textInfo);
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
	
	void ResourceManager::loadGrapefruktXML(const std::string & xmlPath, const std::string & secondXMLPath){
	    
	    
	    XmlSerializer serializer;

	    if(secondXMLPath != ""){
		std::string texturePath;

		Value value;
		Value animation;
		Value textures;
		serializer.readFromFile(xmlPath, value);
		if(!value["Animations"].isNull()){
		    animation = value;
			serializer.readFromFile(secondXMLPath, textures);
			texturePath = ResourcePathHandler::getPathFromFilename(secondXMLPath);
		}
		else{
		    
		    textures = value;
			texturePath = ResourcePathHandler::getPathFromFilename(xmlPath);
			serializer.readFromFile(secondXMLPath, animation);
		}
		loadGrapefruktTextures(textures, texturePath);
		loadGrapefruktSymbols(animation);
	    }
	    else{
		std::string dirPath = ResourcePathHandler::getPathFromFilename(xmlPath);
		Value value;
		serializer.readFromFile(xmlPath, value);
		loadGrapefruktTextures(value["Textures"], dirPath);
		loadGrapefruktSymbols(value["Animations"]);
	    }
	}

	
	void ResourceManager::loadGrapefruktSymbols(Value & node){
	   
	    //if there is more than one texture for the font.
	       Array animations = node["Animation"].getArray();
	       for(Array::iterator i = animations.begin(); i != animations.end(); i++){
		   const std::string & className = (*i)["className"].getString();
			Symbol * symbol = new Symbol();
			symbol->key = (*i)["className"].getString();
			
			symbol->frameCount = (*i)["frameCount"].getInt();
			symbols[symbol->key] = symbol;
	       }  
	       
	       for(Array::iterator i = animations.begin(); i != animations.end(); i++){
		   Array part = (*i)["Part"].getArray();
		   Symbol * parent = symbols[(*i)["className"].getString()];
		   for(Array::iterator j = part.begin(); j != part.end(); j++){
		       std::map<std::string, Symbol*>::iterator found = symbols.find((*j)["className"].getString());
		       if(found != symbols.end()){
			Symbol * child  = symbols[(*j)["className"].getString()];
			if(child == NULL){
			    
			}
			//child->name = (*j)["name"].getString();
			parent->parts.push_back(std::pair<std::string, Symbol*>((*j)["name"].getString(), child));
			
			Array frame = (*j)["Frame"].getArray();
			for(Array::iterator k = frame.begin(); k != frame.end(); k++){
			    int frameIndex = (*k)["index"].getInt();
			    child->frame.insert(frameIndex);
			    Matrix matrix;
			    if((*k)["a"].isNumeric()) matrix.a = (*k)["a"].getFloat();
			    if((*k)["b"].isNumeric()) matrix.b = (*k)["b"].getFloat();
			    if((*k)["c"].isNumeric()) matrix.c = (*k)["c"].getFloat();
			    if((*k)["d"].isNumeric()) matrix.d = (*k)["d"].getFloat();
			    if((*k)["tx"].isNumeric()) matrix.tx = (*k)["tx"].getFloat();
			    if((*k)["ty"].isNumeric()) matrix.ty = (*k)["ty"].getFloat();
			    child->frameMatrices[frameIndex] = matrix;
			}
		    }  
		   }
		}
	    
	}
		
	void ResourceManager::loadGrapefruktTextures(Value & node, const std::string & dirPath){
	 
	    //if there is more than one texture for the font.
	       Array textures = node["TextureSheet"].getArray();
	       for(Array::iterator i = textures.begin(); i != textures.end(); i++){
		   std::string name =(*i)["Texture"]["name"].getString();
		   std::string path = dirPath + '/' + (*i)["Texture"]["path"].getString();
		   Symbol * symbol = new Symbol();
		   symbol->isTexture = true;
		   symbol->key = name;
		   Vector2 registrationPoint;
		   if((*i)["Texture"]["registrationPointX"].isNumeric()) registrationPoint.x = (*i)["Texture"]["registrationPointX"].getFloat();
		   if((*i)["Texture"]["registrationPointY"].isNumeric()) registrationPoint.y = (*i)["Texture"]["registrationPointY"].getFloat();
		   symbol->registrationPoint = registrationPoint;
		   symbols[name] = symbol;
		   registerTexture (name, path);
	       }  
	    
	}

	
	
	
	Font *ResourceManager::initFontFromPath(const std::string &key,
		                      const std::string &path){
	    
	    if(path.substr(path.find_last_of(".") + 1) == "fnt") {
		return initFontFromPathAndFormat(key, path, FontFormat::BMFONT);
	    } 
	    Console__error("Error initializing font " << key);
	    return NULL;
	}
	
	Font *ResourceManager::initFontFromPathAndFormat(const std::string &key,
		                      const std::string &path, const FontFormat & format){
#if ! defined (BB_FLASH_PLATEFORM)
	    if(format == FontFormat::BMFONT){
		BMFont* font = new BMFont(key);
		font->format = format;
		font->loadFontFile(path);
		return font;
		
	    }
#endif
	    Console__error("No font fit the given format");
	    return NULL;
	}
	    
	
	Font *ResourceManager::loadFont(const std::string &key, const std::string &path, bool overwrite) {
		Font *aFont = NULL;

		// We check if there is already a font with this name.
		if (fonts.find(key) != fonts.end()) {
			// We check if we overwrite the existing font or not.
			if (overwrite) {
				// We free the allocated memory.
				aFont = fonts[key];

				if (aFont) {
					delete aFont;
				}

				// We load the new font.
				aFont = fonts[key] = initFontFromPath(key, path);
				Console::println("Overwrote the existing font named " + key + ".");

			} else {
				Console::println("Can't load font with key: " + key +
				                 " font is already loaded");
				aFont = fonts[key];
			}

		} else {
			// We load the new texture and add it to the map.
			aFont = initFontFromPath(key, path);
			fonts.insert(std::pair<std::string, Font *>(key, aFont));
		}

		return aFont;
	}

	Font *ResourceManager::loadFontRelativePath(const std::string &key,
	                                            const std::string &relativePath,
	                                            bool overwrite) {
		return loadFont(key, ResourcePathHandler::getResourcePathFor(relativePath), overwrite);
	}

	Font *ResourceManager::getFont(const std::string &key) {
		std::map<std::string, Font *>::iterator itr = fonts.find(key);
		return (itr != fonts.end()) ? (itr->second) : (NULL);
	}

	void ResourceManager::removeFont(const std::string &key) {
		std::map<std::string, Font *>::iterator i = fonts.find(key);

		if (i != fonts.end()) {
			delete(*i).second;
		}

		fonts.erase(i);
	}
	void ResourceManager::unloadAll() {
		// We unload the textures.
		for (std::map<std::string, TextureInformation *>::iterator i = textures.begin();
		     i != textures.end(); ++i) {
			delete i->second;
		}

		textures.clear();

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
#ifndef BB_ANDROID

		// We unload the fonts.
		for (std::map<std::string, Font *>::iterator i = fonts.begin();
		     i != fonts.end(); ++i) {
			delete i->second;
		}

		fonts.clear();
#endif
	}

	PixMap *ResourceManager::loadPixMap(const std::string &filePath, ColorFormat colorFormat) {
		PixMap *pixmap = loadPixMapFromPNG(filePath);

		if (pixmap && colorFormat == ColorFormat::ALPHA) {
			pixmap->convertTo(ColorFormat::ALPHA);
		}

		return pixmap;
	}

	PixMap *ResourceManager::loadPixMap(const std::string &filePath,
	                                    const Color &transparentColor) {
		PixMap *result = loadPixMap(filePath, ColorFormat(ColorFormat::RGBA));

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
			return false;
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
		png_byte *PNG_image_buffer = (png_byte *)malloc(4 * width * height);
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
									Console::printTrace();
								}
							} else {
								Console::println("Error while writing bytes to PNG file.");
								Console::printTrace();
							}
							
						} else {
							Console::println("Error while writing PNG header.");
							Console::printTrace();
						}
					} else {
						Console::println("Error during init_io.");
						Console::printTrace();
					}
					
				} else {
					Console::println("png_create_info_struct failed.");
					Console::printTrace();
				}
			} else {
				Console::println("png_create_write_struct failed.");
				Console::printTrace();
			}
			fclose(fp);
		} else {
			Console::print("Could not write the PixMap to the PNG file ");
			Console::print(filePath);
			Console::println(".");
			Console::printTrace();
		}
	}
}
