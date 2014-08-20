#ifndef BB_LOCALIZATIONMANAGER_H
#define BB_LOCALIZATIONMANAGER_H
#include <map>
#include <string>
#include <set>
#include "BaconBox/Display/Text/TextEntity.h"
#include "BaconBox/Core/Singleton.h"
namespace BaconBox {
	
    class LocalizationManager : public Singleton {
		BB_SINGLETON_DECL(LocalizationManager);
	public:
		void loadTranslationXML(const std::string &key, const std::string & xmlPath);
		std::map<std::string, std::string> * getTranslations(const std::string &key);

		void setLocal(const std::string &local);
		std::map<std::string, std::string> * getCurrentTranslations();
		
		void addTextEntity(TextEntity * tf);
		void removeTextEntity(TextEntity * tf);
		
	private:
		typedef std::set<TextEntity*> ManagedTextEntities;
		typedef std::map<std::string, std::string> LocalizedStrings;
		typedef std::map<std::string, LocalizedStrings > Localizations;

		ManagedTextEntities managedTextEntities;
		std::map<std::string, std::string> * currentTranslations;
		std::string local;
		Localizations translations;
		LocalizationManager();
		~LocalizationManager();
		
	};
}

#endif


