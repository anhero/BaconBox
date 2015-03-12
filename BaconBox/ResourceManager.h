/**
 * @file
 * @ingroup Display
 * @ingroup Audio
 */
#ifndef BB_RESOURCE_MANAGER_H
#define BB_RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "BaconBox/Audio/SoundParameters.h"
#include "BaconBox/Audio/MusicParameters.h"
#include "BaconBox/Display/PixMap.h"
#include "Display/SubTextureInfo.h"
#include "Display/Text/FontFormat.h"


#include "BaconBox/Helper/Serialization/Value.h"
#include "Symbol.h"


#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

#define BB_MAX_FONT_SIZE 9999
namespace BaconBox {
	class SoundFX;
	class Symbol;
	class BackgroundMusic;
	struct SoundInfo;
	struct MusicInfo;
	struct TextureInformation;
	class Color;
	class Font;
	

	
	/**
	 * Class that manages resources like textures and audio.
	 * @ingroup Display
	 * @ingroup Audio
	 */
	class ResourceManager {
		friend class BaseEngine;
	public:
	    #if !defined(BB_FLASH_PLATFORM)

		static SubTextureInfo *addSubTexture(const std::string &key, SubTextureInfo *textureInfo,
		                                      bool overwrite = false);
		
		
		static TextureInformation *createRenderTexture(const std::string &key,
													   unsigned int width,
													   unsigned int height,
													   ColorFormat::type colorFormat = ColorFormat::RGBA,
		                                      bool overwrite = false);
	    


		
		
		static TextureInformation * loadTexture(PixMap *aPixmap, TextureInformation * texture = NULL);

		static TextureInformation *loadTexture(const std::string &key,
		                                       const std::string &filePath,
		                                       ColorFormat::type colorFormat = ColorFormat::RGBA);
		
		static TextureInformation *loadTextureRelativePath(const std::string &key,
		                                       const std::string &filePath,
		                                       ColorFormat::type colorFormat = ColorFormat::RGBA);
		
		static TextureInformation *loadTexture(TextureInformation * texture);

		
		static TextureInformation *loadTexture(const std::string &key);
		
		
		static TextureInformation * registerTexture(const std::string &key,
		                                       const std::string &filePath,
		                                       ColorFormat::type colorFormat = ColorFormat::RGBA);
		
		
		static TextureInformation * registerTextureRelativePath(const std::string &key,
													const std::string &filePath,
													ColorFormat::type colorFormat = ColorFormat::RGBA);
        
        

		static void removeTexture(const std::string &key);
	
	        static void unloadTexture(const std::string &key);
		static void unloadAllTexture();
		static void unloadAllTextureExcept(const std::set<std::string> exceptions);


		static void deleteAllTexture();
		static void deleteAllSubTexture();

		/**
		 * Gets the information about the asked texture. Uses the texture's key
		 * to find it.
		 * @param key Key used to identify and find the asked texture.
		 * @return Pointer to the texture requested, NULL if no texture is
		 * associated with the given key.
		 */
		static TextureInformation *getTexture(const std::string &key);
		static SubTextureInfo *getSubTexture(const std::string &key, bool loadTextureIfNotLoaded = true);


		/// Create a PixMap from an image file at the given path.
		static PixMap *loadPixMap(const std::string &filePath, ColorFormat::type colorFormat);
		
		/**
		 * Loads a pixmap from a file and sets a specific color as transparent.
		 * @param filePath Path to the file to read.
		 * @param transparentColor Color to be made transparent.
		 */
		static PixMap *loadPixMap(const std::string &filePath,
		                          const Color &transparentColor);
		
		/**
		 * Saves a PixMap to a file at the given path.
		 * @param pixMap PixMap to save to a file.
		 * @param filePath Path to the file to write.
		 */
		static void savePixMap(const PixMap &pixMap,
							   const std::string &filePath);

		static void loadFlashExporterXML(const std::string & xmlPath);
		
		static void loadFlashExporterSymbols(rapidxml::xml_node<> *node);
		
		static void loadFlashExporterTextures(rapidxml::xml_node<> *node,  const std::string & dirPath);
		static bool isLoadedTexture(const std::string & key);

		#endif

		static void deleteAllSymbol();
		
		static void deleteAll();


		static Symbol *addSymbol(const std::string &key, Symbol * symbol = NULL, bool overwrite = false);
		static Symbol *getSymbol(const std::string &key);
		/// Checks whether a symbol exists for the given key.
		static bool symbolExists(const std::string &key);
		/**
		 * Gets a pointer to the asked sound effect.
		 * @param key Name of the sound effect to get a pointer of.
		 * @return Pointer to the asked sound effect, NULL if it doesn't exist.
		 */
		static SoundInfo *getSound(const std::string &key);

		/**
		 * Gets a pointer to the asked background music.
		 * @param key Name of the background music to get a pointer of.
		 * @return Pointer to the asked background music, NULL if it doesn't
		 * exist.
		 */
		static MusicInfo *getMusic(const std::string &key);

		/**
		 * Loads a sound effect.
		 * @param key Name to give to the sound effect.
		 * @param filePath Path to the sound file to load.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded sound effect. Returns NULL if the
		 * loading failed.
		 */
		static SoundInfo *loadSound(const std::string &key,
		                            const std::string &filePath,
		                            bool overwrite = false);

		/**
		 * Loads a sound effect. This version of the loadSound function needs
		 * a relative path from the resource folder, you cannot use an absolute
		 * path or pass your filename through
		 * ResourcePathHandler::getResourcePathFor.
		 * @param key Name to give to the sound effect.
		 * @param relativePath Relative path (relative to the resources folder)
		 * to the sound file to load.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded sound effect. Returns NULL if the
		 * loading failed.
		 */
		static SoundInfo *loadSoundRelativePath(const std::string &key,
		                                        const std::string &relativePath,
		                                        bool overwrite = false);

		/**
		 * Loads a sound effect.
		 * @param info Information in a struct about the sound effect to load.
		 * Let's the developer specify more precise parameters for specific
		 * engines.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded sound effect, NULL if the loading
		 * failed.
		 */
		static SoundInfo *loadSound(const SoundParameters &info,
		                            bool overwrite = false);
		
		static SoundInfo *loadSoundFromBundle(const std::string &key,
		                            const std::string &bundleKey,
		                            bool overwrite = false);
		
		static MusicInfo *loadMusicFromBundle(const std::string &key,
		                            const std::string &bundleKey,
		                            bool overwrite = false);

		/**
		 * Loads a background music.
		 * @param key Name to give to the background music.
		 * @param filePath Path to the music file to load.
		 * @param overwrite Flag checked to know if the loaded music will
		 * oerwrite the existing music if the key already exists.
		 * @return Pointer to the loaded music, NULL if the loading failed.
		 */
		static MusicInfo *loadMusic(const std::string &key,
		                            const std::string &filePath,
		                            bool overwrite = false);

		/**
		 * Loads a background music. This version of the loadMusic function
		 * needs a relative path from the resources folder, you cannot use an
		 * absolute path or pass your filename through
		 * ResourcePathHandler::getResourcePathFor.
		 * @param key Name to give to the background music.
		 * @param relativePath Relative path (relative to the resources folder)
		 * to the music file to load.
		 * @param overwrite Flag checked to know if the loaded music will
		 * oerwrite the existing music if the key already exists.
		 * @return Pointer to the loaded music, NULL if the loading failed.
		 */
		static MusicInfo *loadMusicRelativePath(const std::string &key,
		                                        const std::string &relativePath,
		                                        bool overwrite = false);

		/**
		 * Loads a background music.
		 * @param info Information in a struct about the sound effect to load.
		 * Let's the developer specify more precise parameters for specific
		 * engines.
		 * @param overwrite Flag checked to know if the loaded sound will
		 * overwrite the existing sound if the key already exists.
		 * @return Pointer to the loaded music, NULL if the loading failed.
		 */
		static MusicInfo *loadMusic(const MusicParameters &info,
		                            bool overwrite = true);

		/**
		 * Removes and unloads a sound effect. Does nothing if no sound effect
		 * is associated with the given key.
		 * @param key Name of the sound effect to unload.
		 */
		static void removeSound(const std::string &key);

		/**
		 * Removes and unloads a background music. Does nothing if no background
		 * music is associated with the given key.
		 * @param key Name of the background music to unload.
		 */
		static void removeMusic(const std::string &key);

	
		
		static void addFontAlias(const std::string &key, const std::string &existingKey);
		
		/**
		 * Loads the font at the specified path and put it in the fonts' map.
		 * @param key Name of the font, it will be the key of the fonts' map.
		 * @param path Path of the font.
		 * @param overwrite Flag checked to know if the loaded font will
		 * overwrite the existing font if the key already exists.
		 * @return Pointer to the loaded font, NULL if the font failed to load.
		 */
		static Font *loadFont(const std::string &key,
		                      const std::string &path, int fontSize = BB_MAX_FONT_SIZE);

		/**
		 * Loads the font at the specified path and put it in the fonts' map.
		 * This version of the loadMusic function needs a relative path from the
		 * resources folder, you cannot use an absolute path or pass your
		 * filename through ResourcePathHandler::getResourcePathFor.
		 * @param key Name of the font, it will be the key of the fonts' map.
		 * @param relativePath Relative path (relative to the resources folder)
		 * to the font file to load.
		 * @param overwrite Flag checked to know if the loaded font will
		 * overwrite the existing font if the key already exists.
		 * @return Pointer to the loaded font, NULL if the font failed to load.
		 */
		static Font *loadFontRelativePath(const std::string &key,
		                                  const std::string &relativePath, int fontSize = BB_MAX_FONT_SIZE);

		/**
		 * Return a pointer to the font specified by the given name.
		 * @param key Key of the font to get.
		 * @return Pointer to the specified font, NULL if no font is found.
		 */
		static Font *getFont(const std::string &key, int fontSize = -1);

		/**
		 * Remove the specified font from the fonts' map.
		 * @param key Key of the font to remove.
		 */
		static void removeFont(const std::string &key, int fontSize = -1);
		
		
		/**
		 * Validates the existence of a file.
		 * @param path Path to the file to test.
		 */
		static bool fileExists(const std::string &path);

	private:
	    
	    #if ! defined(BB_FLASH_PLATFORM)
			static TextureInformation *addTextureInfo(const std::string &key, TextureInformation *textureInfo,
					                                      bool overwrite = false);


			///Create a PixMap from a PNG file at the given path.
			static PixMap *loadPixMapFromPNG(const std::string &filePath);
			
			/**
			 * Saves a PixMap to a PNG file.
			 * @param pixMap PixMap to save to a PNG file.
			 * @param filePath Path to the PNG file to write.
			 */
			static void savePixMapToPNG(const PixMap &pixMap, const std::string &filePath);

			/// Map associating the textures' keys and their information.
			static std::map<std::string, TextureInformation *> textures;
			static std::map<std::string, SubTextureInfo *> subTextures;

		#endif

	    
		static Font *initFontFromPath(const std::string &key,
		                      const std::string &path);
		
		static Font *initFontFromPathAndFormat(const std::string &key,
		                      const std::string &path, const FontFormat & format);
		
		
		
		
	    
	

		


		

		/// Map associating the sound effects' names and their information.
		static std::map<std::string, SoundInfo *> sounds;

		/// Map associating the musics' names and their information.
		static std::map<std::string, MusicInfo *> musics;
		/// Map  associating the fonts' names and their information.
		static std::map<std::string, std::map<int, Font *> > fonts;
		static std::map<std::string, Symbol*> symbols;
		
		

	};
}

#endif
