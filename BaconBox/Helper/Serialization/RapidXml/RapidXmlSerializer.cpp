#include "RapidXmlSerializer.h"

#include <cstring>
#include <ctype.h>

#include <set>
#include <sstream>
#include <algorithm>
#include <string>
#include <functional>
#include <locale>

#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

#include "BaconBox/Helper/Serialization/Value.h"
#include "BaconBox/Helper/Serialization/Array.h"
#include "BaconBox/Helper/Serialization/Object.h"
#include "BaconBox/Helper/Parser.h"

namespace BaconBox {
	const std::string FALSE_STRING = std::string("false");
	const std::string TRUE_STRING = std::string("true");

	void nodeToValue(const rapidxml::xml_node<> *node, Value &value);
	
	void valueToNode(const Value &value, rapidxml::xml_node<> *node);

	void attributeToValue(const rapidxml::xml_attribute<> *attribute, Value &value);
	
	void valueToAttribute(const Value &value, rapidxml::xml_attribute<> *attribute);

	void textToValue(const std::string &text, Value &value);
	
	void arrayToNode(const Array &array, rapidxml::xml_node<> *node);
	
	void objectToNode(const Object &object, rapidxml::xml_node<> *node);

	RapidXmlSerializer::RapidXmlSerializer() : Serializer() {
	}

	RapidXmlSerializer::RapidXmlSerializer(const RapidXmlSerializer &src) : Serializer(src) {
	}

	RapidXmlSerializer::~RapidXmlSerializer() {
	}

	RapidXmlSerializer &RapidXmlSerializer::operator=(const RapidXmlSerializer &src) {
		this->Serializer::operator=(src);

		return *this;
	}

	void RapidXmlSerializer::writeToStream(std::ostream &output,
	                                       const Value &value) {
	}

	bool RapidXmlSerializer::readFromStream(std::istream &input, Value &value) {
		bool result = true;
		
		// We initialize the document.
		rapidxml::xml_document<> doc;
		
		// We read the document from the stream.
		rapidxml::file<> inputXml(input);
		
		doc.parse<0>(inputXml.data());
		
		// We get the root element.
		rapidxml::xml_node<> *root = doc.first_node();
		
		// We make sure the document has a root element.
		if (root) {
			value.setName(root->name());
			// We convert the root element into a value.
			nodeToValue(root, value);
		} else {
			result = false;
		}
		
		return result;
	}

	void nodeToValue(const rapidxml::xml_node<> *node, Value &value) {
		// We make sure to set that the value is not an attribute.
		value.setAttribute(false);

		// We check if we have to make an array out of the value.
		bool isArray = false;
		rapidxml::xml_node<> *child = node->first_node();

		while (!isArray && child) {
			if (child->type() == rapidxml::node_data) {
				isArray = true;

			} else {
				child = child->next_sibling();
			}
		}
		
		const rapidxml::xml_attribute<> *attribute = node->first_attribute();
		
		if (isArray) {
			// We start by converting the attributes.
			while (attribute) {
				value.pushBackArray();
				attributeToValue(attribute, value[value.getArray().size() - 1][attribute->name()]);
				attribute = attribute->next_attribute();
			}
			
			// We then convert the child elements.
			child = node->first_node();
			
			while (child) {
				if (child->type() == rapidxml::node_element) {
					value.pushBackArray();
					nodeToValue(child, value[value.getArray().size() - 1][child->name()]);
				} else if (child->type() == rapidxml::node_data) {
					value.pushBackArray();
					textToValue(child->value(), value[value.getArray().size() - 1]);
				}
				
				child = child->next_sibling();
			}
		} else {
			// We start by converting the attributes.
			while (attribute) {
				attributeToValue(attribute, value[attribute->name()]);
				attribute = attribute->next_attribute();
			}
			
			// We then convert the child elements.
			child = node->first_node();
			Object::const_iterator itFound;
			
			while (child) {
				// We only read the child elements (we already know there are no
				// text children.
				if (child->type() == rapidxml::node_element) {
					// We check if the value already contains a member with that
					// name.
					itFound = value.getObject().find(child->name());
					
					if (itFound != value.getObject().end()) {
						Value &found = value[child->name()];
						
						if (!found.isArray()) {
							Value tmp(found);
							found.setArray(Array(1, tmp));
							found.setArrayOfSameTypes(true);
						}
						
						found.pushBackArray();
						nodeToValue(child, found[found.getArray().size() - 1]);
					} else {
						// If it's a new member name, we simply add it to the
						// value.
						nodeToValue(child, value[child->name()]);
					}
				}
				
				child = child->next_sibling();
			}
		}
	}
	
	void valueToNode(const Value &value, rapidxml::xml_node<> *node) {
		// If the value to convert is an array.
		if (value.isArray()) {
			arrayToNode(value.getArray(), node);
			// If the value to convert is an object.
		} else if (value.isObject()) {
			objectToNode(value.getObject(), node);
			
			// If it's a numeric, a string, a boolean or a null value.
		} else {
			rapidxml::xml_node<> *newChild = node->document()->allocate_node(rapidxml::node_data);
			newChild->value(node->document()->allocate_string(value.getToString().c_str()));
			node->append_node(newChild);
		}
	}
	
	void attributeToValue(const rapidxml::xml_attribute<> *attribute, Value &value) {
		value.setAttribute(true);
		textToValue(attribute->value(), value);
	}
	
	void valueToAttribute(const Value &value, rapidxml::xml_attribute<> *attribute) {
		if (value.isStringable()) {
			attribute->value(attribute->document()->allocate_string(value.getToString().c_str()));
		}
	}
	
	void textToValue(const std::string &text, Value &value) {
		if (text.empty()) {
			// If the text is empty, it's a null value.
			value.setNull();

		} else {
			if (Parser::isNumeric(text)) {
				if (Parser::isInteger(text)) {
					// No errors? Therefore, it's an integer.
					value.setInt(Parser::stringToInt(text));

				} else {
					value.setDouble(Parser::stringToDouble(text));
				}

			} else {
				// It's neither an integer nor a floating point number, so let's
				// check if it's a boolean value.
				std::string tmpString(text);
				std::transform(tmpString.begin(),
				               tmpString.end(),
				               tmpString.begin(),
				               ::tolower);
				bool isBoolean = true;
				std::string::const_iterator i = tmpString.begin();
				std::locale loc;

				while (isBoolean && i != tmpString.end()) {
					// There can be white spaces before and after the
					// "false" or "true" values.
					if (!std::isspace(*i, loc)) {
						// If we've already found the bool value and we've
						// found another non-whitespace character, it means
						// it's only a string that starts with the "false"
						// or "true" value.
						if (value.isBoolean()) {
							isBoolean = false;

						} else {
							// We check that it contains the "false" or
							// "true" value.
							if (std::equal(FALSE_STRING.begin(), FALSE_STRING.end(), i)) {
								value.setBool(false);
								std::advance(i, FALSE_STRING.size());

							} else if (std::equal(TRUE_STRING.begin(), TRUE_STRING.end(), i)) {
								value.setBool(true);
								std::advance(i, TRUE_STRING.size());

							} else {
								// If not, it means it's not a boolean
								// either.
								isBoolean = false;
							}
						}

					} else {
						++i;
					}
				}

				// If it's not a boolean, it can only be a string.
				if (!isBoolean) {
					value.setString(text);
				}

			}
		}
	}
	
	void arrayToNode(const Array &array, rapidxml::xml_node<> *node) {
		rapidxml::xml_node<> *newChild;
		
		// We check each element of the array.
		for (Array::size_type i = 0; i < array.size(); ++i) {
			// If the element in the array is an object.
			if (array[i].isObject()) {
				objectToNode(array[i].getObject(), node);
			} else if (array[i].isArray()) {
				arrayToNode(array[i].getArray(), node);
			} else if (array[i].isStringable()) {
				newChild = node->document()->allocate_node(rapidxml::node_data);
				newChild->value(node->document()->allocate_string(array[i].getToString().c_str()));
				node->append_node(newChild);
			}
		}
	}
	
	void objectToNode(const Object &object, rapidxml::xml_node<> *node) {
		rapidxml::xml_node<> *newChild;
		
		// We check each values in the object.
		for (Object::const_iterator i = object.begin(); i != object.end(); ++i) {
			// If the value is an attribute.
			if (i->second.isAttribute()) {
				// We check if it can be converted to a string, if not, we'll
				// make it a normal element.
				if (i->second.isStringable()) {
					// We set the attribute.
					node->append_attribute(node->document()->allocate_attribute(node->document()->allocate_string(i->first.c_str()), node->document()->allocate_string(i->second.getToString().c_str())));
				} else {
					// We create a new element and add it to the current
					// element.
					newChild = node->document()->allocate_node(rapidxml::node_element);
					newChild->name(node->document()->allocate_string(i->first.c_str()));
					valueToNode(i->second, newChild);
					node->append_node(newChild);
				}
			} else {
				if (i->second.isArrayOfSameTypes()) {
					const Array &tmpArray = i->second.getArray();
					
					for (Array::size_type j = 0; j < tmpArray.size(); ++j) {
						newChild = node->document()->allocate_node(rapidxml::node_element);
						newChild->name(node->document()->allocate_string(i->first.c_str()));
						valueToNode(tmpArray[j], newChild);
						node->append_node(newChild);
					}
				} else {
					// We create a new element and add it to the current
					// element.
					newChild = node->document()->allocate_node(rapidxml::node_element);
					newChild->name(node->document()->allocate_string(i->first.c_str()));
					valueToNode(i->second, newChild);
					node->append_node(newChild);
				}
			}
		}
	}
}
