#include "FlashExporterXmlReader.h"

#include <cstring>

#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

#include "BaconBox/Helper/ResourcePathHandler.h"
#include "BaconBox/Symbol.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	static const char *TRUE_STRING = "true";
	
	static const char *LEFT_ALIGNMENT = "left";
	static const char *CENTER_ALIGNMENT = "center";
	static const char *RIGHT_ALIGNMENT = "right";
	
	static const char *TEXTURE_SHEET_NODE_NAME = "TextureSheet";
	static const char *SYMBOLS_NODE_NAME = "Symbols";
	static const char *SYMBOL_NODE_NAME = "Symbol";
	static const char *TEXTURE_NODE_NAME = "Texture";

	static const char *CLASS_NAME_NODE_NAME = "className";
	static const char *TEXT_FIELD_NODE_NAME = "textfield";
	static const char *TEXT_NODE_NAME = "text";
	static const char *FONT_NODE_NAME = "font";
	static const char *ALIGNMENT_NODE_NAME = "alignment";
	static const char *WIDTH_NODE_NAME = "width";
	static const char *HEIGHT_NODE_NAME = "height";
	static const char *FRAME_COUNT_NODE_NAME = "frameCount";
	static const char *FRAME_NODE_NAME = "Frame";
	static const char *CHILD_NODE_NAME = "Child";
	static const char *NAME_NODE_NAME = "name";
	static const char *A_NODE_NAME = "a";
	static const char *B_NODE_NAME = "b";
	static const char *C_NODE_NAME = "c";
	static const char *D_NODE_NAME = "d";
	static const char *TX_NODE_NAME = "tx";
	static const char *TY_NODE_NAME = "ty";

	void FlashExporterXmlReader::readFile(const std::string &path, const std::string &secondPath) {
		if (!secondPath.empty()) {
			// We initialize the document.
			rapidxml::xml_document<> doc;

			// We read the document at the given file location.
			rapidxml::file<> inputXml(path.c_str());

			doc.parse<0>(inputXml.data());

			// We get the root element.
			rapidxml::xml_node<> *root = doc.first_node();

			// We make sure the document has a root element.
			if (root && std::strcmp(root->name(), TEXTURE_SHEET_NODE_NAME) == 0) {
				rapidxml::xml_node<> *animation;
				rapidxml::xml_node<> *textures;
				std::string texturePath;

				// We initialize the second document.
				rapidxml::xml_document<> secondDoc;

				// We read the second document at the given file location.
				rapidxml::file<> secondInputXml(secondPath.c_str());

				secondDoc.parse<0>(secondInputXml.data());

				rapidxml::xml_node<> *symbolsNode = root->first_node(SYMBOLS_NODE_NAME);

				if (!symbolsNode) {
					animation = symbolsNode;
					textures = secondDoc.first_node();

					texturePath = ResourcePathHandler::getPathFromFilename(secondPath);

				} else {
					textures = root->first_node(TEXTURE_NODE_NAME);
					texturePath = ResourcePathHandler::getPathFromFilename(path);
					animation = secondDoc.first_node();
				}

				// We make sure the two nodes are valid.
				if (textures && animation) {
					loadTextures(textures, texturePath);
					loadSymbols(animation);

				} else {
					Console::println("One of the two given XML files doesn't have a root element.");
				}

			} else {
				Console::println("The root node name is invalid, it should be TextureSheet.");
			}
		} else {
			std::string dirPath = ResourcePathHandler::getPathFromFilename(path);

			// We initialize the document.
			rapidxml::xml_document<> doc;

			// We read the document at the given file location.
			rapidxml::file<> inputXml(path.c_str());

			doc.parse<0>(inputXml.data());

			// We get the root element.
			rapidxml::xml_node<> *root = doc.first_node();

			// We make sure the document has a root element.
			if (root && std::strcmp(root->name(), TEXTURE_SHEET_NODE_NAME) == 0) {
				// We get the "Symbols" node and the "Texture" node.
				rapidxml::xml_node<> *symbolsNode = NULL;
				rapidxml::xml_node<> *textureNode = NULL;
				rapidxml::xml_node<> *current = root->first_node();

				while (current && (!symbolsNode || !textureNode)) {
					if (current->type() == rapidxml::node_element) {
						if (!symbolsNode && std::strcmp(current->name(), SYMBOLS_NODE_NAME) == 0) {
							symbolsNode = current;

						} else if (!textureNode && std::strcmp(current->name(), TEXTURE_NODE_NAME)) {
							textureNode = current;
						}
					}

					current = current->next_sibling();
				}

				if (symbolsNode && textureNode) {
					this->loadTextures(textureNode, dirPath);
					this->loadSymbols(symbolsNode);
				}
			}
		}
	}

	void FlashExporterXmlReader::loadSymbols(rapidxml::xml_node<> *node) {
		rapidxml::xml_node<> *symbolNode = node->first_node();

		while (symbolNode) {
			if (std::strcmp(symbolNode->name(), SYMBOL_NODE_NAME) == 0) {
				this->loadSymbol(symbolNode);
			}

			symbolNode = symbolNode->next_sibling();
		}
	}

	void FlashExporterXmlReader::loadSymbol(rapidxml::xml_node<> *node) {
		Symbol *symbol = new Symbol();

		rapidxml::xml_node<> *current = node->first_node();
		rapidxml::xml_node<> *classNameNode = NULL;
		rapidxml::xml_node<> *textFieldNode = NULL;

		while (current && (!classNameNode || !textFieldNode)) {
			if (current->type() == rapidxml::node_element) {
				if (!classNameNode && std::strcmp(current->name(), CLASS_NAME_NODE_NAME) == 0) {
					classNameNode = current;

				} else if (!textFieldNode && std::strcmp(current->name(), TEXT_FIELD_NODE_NAME)) {
					textFieldNode = current;
				}
			}

			current = current->next_sibling();
		}
		
		if (classNameNode) {
			symbol->key = classNameNode->value();
		}
		
		if (textFieldNode) {
			symbol->isTextField = (std::strcmp(textFieldNode->value(), TRUE_STRING) == 0);
		}
		
		if (symbol->isTextField) {
			symbol->frameCount = 1;
			
			rapidxml::xml_node<> *textNode = NULL;
			rapidxml::xml_node<> *fontNode = NULL;
			rapidxml::xml_node<> *alignmentNode = NULL;
			rapidxml::xml_node<> *widthNode = NULL;
			rapidxml::xml_node<> *heightNode = NULL;
			
			current = node->first_node();
			
			while (current && (!textNode || !fontNode || !alignmentNode || !widthNode || !heightNode)) {
				if (current->type() == rapidxml::node_element) {
					if (!textNode && std::strcmp(current->name(), TEXT_NODE_NAME) == 0) {
						textNode = current;
					} else if (!fontNode && std::strcmp(current->name(), FONT_NODE_NAME) == 0) {
						fontNode = current;
					} else if (!alignmentNode && std::strcmp(current->name(), ALIGNMENT_NODE_NAME) == 0) {
						alignmentNode = current;
					} else if (!widthNode && std::strcmp(current->name(), WIDTH_NODE_NAME) == 0) {
						widthNode = current;
					} else if (!heightNode && std::strcmp(current->name(), HEIGHT_NODE_NAME) == 0) {
						heightNode = current;
					}
				}
				
				current = current->next_sibling();
			}
			
			if (textNode) {
				symbol->text = textNode->value();
			}
			
			if (fontNode) {
				symbol->font = fontNode->value();
			}
			
			if (alignmentNode) {
				char *value = alignmentNode->value();
				
				if (std::strcmp(value, LEFT_ALIGNMENT) == 0) {
					symbol->alignment = TextAlignment::LEFT;
				} else if (std::strcmp(value, CENTER_ALIGNMENT) == 0) {
					symbol->alignment = TextAlignment::CENTER;
				} else if (std::strcmp(value, RIGHT_ALIGNMENT)) {
					symbol->alignment = TextAlignment::RIGHT;
				}
			}
			
			if (widthNode) {
				symbol->textFieldWidth = std::atoi(widthNode->value());
			}
			
			if (heightNode) {
				symbol->textFieldHeight = std::atoi(heightNode->value());
			}
			
		} else {
			current = node->first_node(FRAME_COUNT_NODE_NAME);
			
			if (current && current->type() == rapidxml::node_element) {
				symbol->frameCount = std::atoi(current->value());
			}
		}
		
		if (!symbol->key.empty()) {
			symbols[symbol->key] = symbol;
		} else {
			Console::println("Trying to load a symbol that doesn't have a name!");
		}
		
		// TODO: finish the function!
	}
}
