/**
 * @deprecated This will eventually all be migrated to the proper FileSystem hierarchy.
 */
#include "BaconBox/Helper/ResourcePathHandler.h"

#include <fstream>

#include "BaconBox/PlatformFlagger.h"
#ifdef BB_IPHONE_PLATFORM
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#elif defined(BB_MAC_PLATFORM) || defined(BB_LINUX) || defined(BB_FLASH_PLATFORM)
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sstream>
#include <string.h>
#elif defined(BB_QT)
#include <QDir>
#include <iostream>
#include <QCoreApplication>
#include <QDesktopServices>
#endif
#include "BaconBox/Console.h"
#include "BaconBox/Core/Engine.h"

#if defined(BB_ANDROID)
	#include "BaconBox/Helper/Android/AndroidHelper.h"
#endif

namespace BaconBox {
	
	std::string ResourcePathHandler::debugResourcePath = "";


	std::string ResourcePathHandler::getResourcePathFor(const std::string &item) {
		std::string path = getResourcePath() + "/" + item;
		return path;
	}
	
	void ResourcePathHandler::setDebugResourcePath(const std::string & path){
		debugResourcePath = path;
	}
	
	std::string ResourcePathHandler::getResourcePath(){
		std::string resourcePath;
#if defined(BB_IPHONE_PLATFORM)

		NSString *resourceDirectory = [[NSBundle mainBundle] resourcePath];
		resourcePath = [resourceDirectory cStringUsingEncoding: NSASCIIStringEncoding];
#elif defined(BB_ANDROID)
		if(debugResourcePath != "") return debugResourcePath;
		return "/data/data/" + AndroidHelper::getPackageName() + "/";
#else
		
if(debugResourcePath != "") return debugResourcePath;
resourcePath = Engine::getApplicationPath();
		
#ifdef BB_MAC_PLATFORM
		resourcePath = resourcePath + "/../Resources";
#else
		resourcePath = resourcePath + "/Resources";
#endif
#endif

		return resourcePath;
	}

	bool ResourcePathHandler::isFileReadable(const std::string &filePath) {
		// We try to open the file for reading.
		std::ifstream file(filePath.c_str());
		bool result = false;

		// If the file is open, it means it can be read.
		if (file.is_open()) {
			result = true;
			// We make sure to close the file.
			file.close();
		}

		return result;
	}
	
	std::string ResourcePathHandler::getPathFromFilename(std::string filename){
		std::string::size_type found = filename.find_last_of("/\\");
	    return filename.substr(0, found);
	}

	bool ResourcePathHandler::isFileWritable(const std::string &filePath) {
		// We try to open the file for writing.
		std::ofstream file(filePath.c_str());
		bool result = false;

		// If the file is open, it means it can be read.
		if (file.is_open()) {
			result = true;
			// We make sure to close the file.
			file.close();
		}

		return result;
	}
}
