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
	}

namespace BaconBox {
	class Singleton {
	public:
		static Singleton& getInstance();
		virtual void destroyInstance() = 0;
	};
}

#endif