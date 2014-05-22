#include "BaconBox/Helper/ResourcePathHandler.h"

#include <fstream>

#include "BaconBox/PlatformFlagger.h"
#ifdef BB_IPHONE_PLATFORM
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#elif defined(BB_MAC_PLATFORM) || defined(BB_LINUX)
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sstream>
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
	
	std::string ResourcePathHandler::debugDocumentPath = "";
	std::string ResourcePathHandler::debugResourcePath = "";


	std::string ResourcePathHandler::getResourcePathFor(const std::string &item) {
		std::string path = getResourcePath() + "/" + item;
// #ifdef BB_IPHONE_PLATFORM

// 		NSString *resourceDirectory = [[NSBundle mainBundle] resourcePath];
// 	path = ((std::string)[resourceDirectory cStringUsingEncoding: NSASCIIStringEncoding] + "/" + item);
// #else
// 		if(debugResourcePath != ""){
// 			path = debugResourcePath + "/" + item;
// 		}
// 		else{
// 			path = Engine::getApplicationPath();
		

// #ifdef BB_MAC_PLATFORM
// 		path = path + "/../Resources/" + item;
// #else
// 		path = path + "/Resources/" + item;
// #endif
// }
// #endif //BB_IPHONE_PLATFORM


		
		return path;
	}
	
	void ResourcePathHandler::setDebugDocumentPath(const std::string & path){
		debugDocumentPath = path;
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

	
	std::string ResourcePathHandler::getDocumentPathFor(const std::string &item) {
		std::string documentPath = getDocumentPath();
		documentPath.append(item);
		return documentPath;
	}

	std::string ResourcePathHandler::getDocumentPath() {
#if defined(BB_IPHONE_PLATFORM)
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *documentsDirectory = [paths objectAtIndex: 0];
	std::string documentPath = [documentsDirectory cStringUsingEncoding: NSASCIIStringEncoding];
		return documentPath;


#else
		if(debugDocumentPath != ""){
			return debugDocumentPath;
		}
		else{
#if defined(BB_MAC_PLATFORM) || (defined(BB_LINUX) && !defined(BB_ANDROID))
		
		

#if defined(BB_MAC_PLATFORM)
		const std::string PATH = "/Library/Application Support/";
#else
		const std::string PATH = "/.config/";
#endif
		static bool firstTime = true;
		std::stringstream ss;

		ss << getpwuid(getuid())->pw_dir << PATH << Engine::getApplicationName() << "/";

		if (firstTime) {
			createFolder(ss.str());
			firstTime = false;
		}

		return ss.str();

#elif defined(BB_ANDROID)
		return "/data/data/" + AndroidHelper::getPackageName() + "/";
#else
		return std::string();
		
		
#endif
		}
#endif
		
	}

	bool ResourcePathHandler::createDocumentFolder(const std::string &path) {
		return createFolderTree(getDocumentPath() +"/" + path);
	}

	bool ResourcePathHandler::createFolder(const std::string &path) {
#if defined(BB_MAC_PLATFORM) || defined(BB_LINUX)|| defined(BB_IPHONE_PLATFORM)
		if (mkdir(path.c_str(), 0755)) {
			return true;

		} else {
			return false;
		}

#else
		return false;
#endif
	}

	bool ResourcePathHandler::createFolderTree(const std::string &path) {
		bool result = false;

		// We make sure the path isn't empty.
		if (!path.empty()) {
			std::string::const_iterator i = path.begin();
			std::string tmpPath;
			tmpPath.reserve(path.size());

#ifdef BB_WINDOWS_PLATFORM

			if (path.size() >= 2 && path.at(1) == ':' && ((path.at(0) >= 'A' && path.at(0) <= 'Z') || (path.at(0) >= 'a' && path.at(0) <= 'z'))) {
				tmpPath.append(path, 0, 2);
				++i;
				++i;
			}

#endif

			// For each character in the path.
			while (!result && i != path.end()) {
				tmpPath.append(1, *i);

				// If we encounter a slash and the folder doesn't already exist,
				// we try to create the folder.
				if (*i == '/' && !folderExists(tmpPath) && createFolder(tmpPath)) {
					Console::print("Failed to create the document folder \"");
					Console::print(tmpPath);
					Console::println("\".");
					result = true;
				}

				++i;
			}

			// If the path didn't end with a slash, we try to create the last
			// folder.
			if (!result && tmpPath.at(tmpPath.size() - 1) != '/' && !folderExists(tmpPath) && createFolder(tmpPath)) {
				Console::print("Failed to create the document folder \"");
				Console::print(tmpPath);
				Console::println("\".");
				result = true;
			}
		}

		return result;
	}
	
	bool ResourcePathHandler::removeDirectory(const std::string &path){
		//Took from here: http://stackoverflow.com/questions/2256945/removing-a-non-empty-directory-programmatically-in-c-or-c

		DIR *d = opendir(path.c_str());
		size_t path_len = strlen(path.c_str());
		int r = -1;
		
		if (d)
		{
			struct dirent *p;
			
			r = 0;
			
			while (!r && (p=readdir(d)))
			{
				int r2 = -1;
				char *buf;
				size_t len;
				
				/* Skip the names "." and ".." as we don't want to recurse on them. */
				if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
				{
					continue;
				}
				
				len = path_len + strlen(p->d_name) + 2;
				buf = (char*)malloc(len);
				
				if (buf)
				{
					struct stat statbuf;
					
					snprintf(buf, len, "%s/%s", path.c_str(), p->d_name);
					
					if (!stat(buf, &statbuf))
					{
						if (S_ISDIR(statbuf.st_mode))
						{
							r2 = removeDirectory(buf);
						}
						else
						{
							r2 = unlink(buf);
						}
					}
					
					free(buf);
				}
				
				r = r2;
			}
			
			closedir(d);
		}
		
		if (!r)
		{
			r = rmdir(path.c_str());
		}
		
		return r;
	}
	
	

	bool ResourcePathHandler::folderExists(const std::string &path) {
#ifdef BB_IPHONE_PLATFORM
		return false;
#elif defined(BB_MAC_PLATFORM) || defined(BB_LINUX)
		struct stat st;
		return stat(path.c_str(), &st) == 0;
#else
		return false;
#endif
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
