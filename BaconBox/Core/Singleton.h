#ifndef BB_SINGLETON_H
#define BB_SINGLETON_H

#include <string>
#include <map>

#include "BaconBox/Core/IDManager.h"

#define BB_SINGLETON_IMPL(cls) cls * cls::instance = NULL; \
	cls& cls::getInstance() { \
		if (!instance) { \
			instance = new cls(); \
			Engine::getInstance().registerSingleton(static_cast<Singleton *>(instance)); \
		} \
		return * instance; \
	} \
	void cls::destroyInstance() { \
		if (cls::instance) delete cls::instance; \
		cls::instance = NULL; \
	} \
	bool cls::hasInstance() { \
		return (cls::instance != NULL); \
	} \
	std::string cls::getName() { \
		return std::string(#cls); \
	} \

#define BB_SINGLETON_DECL(cls) \
	public:\
	static cls &getInstance(); \
	void destroyInstance(); \
	static bool hasInstance(); \
	std::string getName(); \
	protected: \
	static cls * instance;



namespace BaconBox {
	class Singleton {
	public:
		// static Singleton& getInstance() = 0;
		virtual void destroyInstance() = 0;
		// static bool hasInstance() = 0;
		virtual std::string getName() = 0;
	};
}

#endif
