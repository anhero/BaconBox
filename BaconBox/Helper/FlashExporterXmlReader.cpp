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

	void readMatrix(rapidxml::xml_node<> *node, Matrix &matrix);

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

		// We load the symbols.
		while (symbolNode) {
			if (symbolNode->type() == rapidxml::node_element && std::strcmp(symbolNode->name(), SYMBOL_NODE_NAME) == 0) {
				this->loadSymbol(symbolNode);
			}

			symbolNode = symbolNode->next_sibling();
		}

		// We load the symbols' children.
		symbolNode = node->first_node();

		while (symbolNode) {
			if (symbolNode->type() == rapidxml::node_element && std::strcmp(symbolNode->name(), SYMBOL_NODE_NAME) == 0) {
				this->loadSymbolChildren(symbolNode);
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

		std::pair<bool, std::map<std::string, Symbol *>::iterator> symbolIt;

		if (!symbol->key.empty()) {
			this->symbols[symbol->key] = symbol;

		} else {
			Console::println("Trying to load a symbol that doesn't have a name!");
		}
	}

	void FlashExporterXmlReader::loadSymbolChildren(rapidxml::xml_node<> *node) {
		rapidxml::xml_node<> *classNameNode = node->first_node(CLASS_NAME_NODE_NAME);

		if (classNameNode) {
			std::map<std::string, Symbol *>::iterator found = this->symbols.find(classNameNode->value());

			if (found != this->symbols.end()) {
				rapidxml::xml_node<> *frameNode = node->first_node(FRAME_NODE_NAME);

				if (frameNode) {
					std::map<std::string, Symbol::Part *> children;
					rapidxml::xml_node<> *currentFrame = frameNode->first_node();

					int frameIndex = 0;
					int index;
					rapidxml::xml_node<> *childrenNode;

					while (currentFrame) {
						if (currentFrame->type() == rapidxml::node_element) {
							index = 0;

							childrenNode = currentFrame->first_node(CHILD_NODE_NAME);

							if (childrenNode) {
								rapidxml::xml_node<> *currentChild = childrenNode->first_node();

								while (currentChild) {
									if (currentChild->type() == rapidxml::node_element) {
										rapidxml::xml_node<> *nameNode = NULL;
										rapidxml::xml_node<> *childClassNameNode = NULL;

										rapidxml::xml_node<> *currentNode = currentChild->first_node();

										while (currentNode && (!nameNode || !childClassNameNode)) {
											if (currentNode->type() == rapidxml::node_element) {
												if (!nameNode && std::strcmp(currentNode->name(), NAME_NODE_NAME)) {
													nameNode = currentNode;

												} else if (!childClassNameNode && std::strcmp(currentNode->name(), CLASS_NAME_NODE_NAME)) {
													childClassNameNode = currentNode;
												}
											}

											currentNode = currentNode->next_sibling();
										}

										std::string name, className;

										if (nameNode) {
											name = nameNode->value();
										}

										if (childClassNameNode) {
											className = childClassNameNode->value();
										}

										if (nameNode && childClassNameNode) {
											Symbol::Part *part;
											std::pair<std::map<std::string, Symbol::Part *>::iterator, bool> inserted = children.insert(std::pair<std::string, Symbol::Part *>(name, NULL));

											if (inserted.second) {
												part = inserted.first->second = new Symbol::Part();
												part->name = name;

												std::map<std::string, Symbol *>::iterator symbolDependency = this->symbols.find(className);

												if (symbolDependency != this->symbols.end()) {
													part->symbol = symbolDependency->second;

												} else {
													part->symbol = NULL;
													Console__error("Trying to add a NULL symbol part with key " << className << " to " << found->second->key);
												}

											} else {
												part = inserted.first->second;
											}

											part->indexByFrame.insert(std::make_pair(frameIndex, index));

											Matrix matrix;

											readMatrix(currentChild, matrix);

											part->matrices.insert(std::make_pair(frameIndex, matrix));

											++index;
										}
									}

									currentChild = currentChild->next_sibling();
								}

								++frameIndex;
							}
						}

						currentFrame = currentFrame->next_sibling();
					}

					for (std::map<std::string, Symbol::Part *>::iterator i = children.begin(); i != children.end(); ++i) {
						found->second->parts.push_back(*i->second);
					}
				}
			}
		}
	}

	void readMatrix(rapidxml::xml_node<> *node, Matrix &matrix) {
		rapidxml::xml_node<> *currentNode = node->first_node();

		rapidxml::xml_node<> *aNode = NULL, *bNode = NULL, *cNode = NULL, *dNode = NULL, *txNode = NULL, *tyNode = NULL;

		while (currentNode && (!aNode || !bNode || !cNode || !dNode || !txNode || !tyNode)) {
			if (currentNode->type() == rapidxml::node_element) {
				if (!aNode && std::strcmp(currentNode->name(), A_NODE_NAME)) {
					aNode = currentNode;

				} else if (!bNode && std::strcmp(currentNode->name(), B_NODE_NAME)) {
					bNode = currentNode;

				} else if (!cNode && std::strcmp(currentNode->name(), C_NODE_NAME)) {
					cNode = currentNode;

				} else if (!dNode && std::strcmp(currentNode->name(), D_NODE_NAME)) {
					dNode = currentNode;

				} else if (!txNode && std::strcmp(currentNode->name(), TX_NODE_NAME)) {
					txNode = currentNode;

				} else if (!tyNode && std::strcmp(currentNode->name(), TY_NODE_NAME)) {
					tyNode = currentNode;
				}
			}

			currentNode = currentNode->next_sibling();
		}

		if (aNode) {
			matrix.a = std::atof(aNode->value());
		}

		if (bNode) {
			matrix.b = std::atof(bNode->value());
		}

		if (cNode) {
			matrix.c = std::atof(cNode->value());
		}

		if (dNode) {
			matrix.d = std::atof(dNode->value());
		}

		if (txNode) {
			matrix.tx = std::atof(txNode->value());
		}

		if (tyNode) {
			matrix.ty = std::atof(tyNode->value());
		}
	}
}
