#include "LocalizationManager.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>
#include "BaconBox/Console.h"
#include "BaconBox/Core/Engine.h"

using namespace BaconBox;

BB_SINGLETON_IMPL(LocalizationManager);

LocalizationManager::LocalizationManager(): currentTranslations(NULL), translations(), managedTextEntities(){

}


void LocalizationManager::setLocal(const std::string &local){
	this->local = local;
	currentTranslations = getTranslations(local);
	if(currentTranslations){
		for (ManagedTextEntities::iterator i = managedTextEntities.begin(); i != managedTextEntities.end(); i++) {
			Symbol* symbol = (*i)->getSymbol();
			if(symbol){
				LocalizedStrings::iterator j = currentTranslations->find(symbol->key);
				if(j != currentTranslations->end()) (*i)->setText(j->second);
			}
		}
	}
	
}

std::map<std::string, std::string> * LocalizationManager::getCurrentTranslations(){
	return currentTranslations;
}

void LocalizationManager::loadTranslationXML(const std::string &key, const std::string &xmlPath) {
	Localizations::iterator i = translations.find(key);
	if( i == translations.end()){
		i = translations.insert(std::pair<std::string, LocalizedStrings >(key, LocalizedStrings())).first;
	}
	
	LocalizedStrings & translationMap = i->second;
	
	rapidxml::xml_document<> doc;
	
	rapidxml::file<> inputXml(xmlPath.c_str());
	doc.parse<0>(inputXml.data());
	rapidxml::xml_node<> *root = doc.first_node();
	rapidxml::xml_attribute<> *textfield;
	for (rapidxml::xml_node<> *node = root->first_node("translation"); node; node = node->next_sibling()){
		textfield = node->first_attribute("key");
		if (textfield) {
			translationMap[textfield->value()] = node->first_attribute("text")->value();
		}
		
	}
	
}
std::map<std::string, std::string> * LocalizationManager::getTranslations(const std::string &key){
	std::map<std::string, std::map<std::string, std::string> >::iterator i = translations.find(key);
	if( i == translations.end()){
		return NULL;
	}
	else{
		return &(i->second);
	}
}

void LocalizationManager::addTextEntity(TextEntity * tf){
	managedTextEntities.insert(tf);
}

void LocalizationManager::removeTextEntity(TextEntity * tf){
	managedTextEntities.erase(tf);
}

LocalizationManager::~LocalizationManager() {
	PRLN("LocalizationManager::~LocalizationManager()");
}



