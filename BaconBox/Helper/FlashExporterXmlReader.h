#ifndef BB_FLASH_EXPORTER_XML_READER_H
#define BB_FLASH_EXPORTER_XML_READER_H

#include <rapidxml.hpp>

#include <string>
#include <map>

namespace BaconBox {
	struct Symbol;
	struct TextureInformation;
	struct SubTextureInfo;

	class FlashExporterXmlReader {
	public:
		FlashExporterXmlReader(std::map<std::string, TextureInformation *> &textures,
		                       std::map<std::string, SubTextureInfo *> &subTextures,
		                       std::map<std::string, Symbol *> &symbols);
		
		void readFile(const std::string &path, const std::string &secondPath);
	private:
		void loadSymbols(rapidxml::xml_node<> *node);
		void loadSymbol(rapidxml::xml_node<> *node);
		void loadSymbolChildren(rapidxml::xml_node<> *node);
		void loadTextures(rapidxml::xml_node<> *node, const std::string &texturePath);
		
		std::map<std::string, TextureInformation *> &textures;
		std::map<std::string, SubTextureInfo *> &subTextures;
		std::map<std::string, Symbol *> &symbols;
	};
}

#endif /* defined(BB_FLASH_EXPORTER_XML_READER_H) */

