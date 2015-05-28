/**
 * @file
 * @ingroup Helper
 */

//RESOURCE_PATH_FOR() macro function
//Iphone
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
//DEPRECATED MACRO, USE getResourcePathFor() INSTEAD!!!
#define RESOURCE_PATH_FOR(path) (char*)((std::string)[[[NSBundle mainBundle] resourcePath] cStringUsingEncoding:NSASCIIStringEncoding] + "/" + path ).c_str()
#endif

#ifndef BB_RESOURCE_PATH_HANDLER_H
#define BB_RESOURCE_PATH_HANDLER_H

#include <string>
namespace BaconBox {
	/**
	 * Functions used to get the resource paths for files. All slashes must be
	 * forward slashes. Backslashes are not treated as folder separators.
	 * @ingroup Helper
	 */
	class ResourcePathHandler {
	public:
		/**
		 * Gets the resource path for a file name.
		 * @return Full resource path for the file.
		 */
		static std::string getResourcePathFor(const std::string& item);
		
		static std::string getResourcePath();

		static void setDebugResourcePath(const std::string & path);
		
		static std::string getPathFromFilename(std::string filename);

		/**
		 * Checks wether or not a file exists and is readable.
		 * @param filePath Path to the file to check its readability.
		 * @return True if the file exists and is readable, false if not.
		 */
		static bool isFileReadable(const std::string &filePath);

		/**
		 * Checks wether or not a file exists and is writable.
		 * @param filePath Path to the file to check its writability.
		 * @return True if the file exists and is writable, false if not.
		 */
		static bool isFileWritable(const std::string &filePath);
	private:
		static std::string debugResourcePath;
		/**
		 * Default constructor, to make sure no one tries to instantiate this
		 * class.
		 */
		ResourcePathHandler();
		
	
	};
}

#endif
