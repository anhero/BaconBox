#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "BaconBox/Core/Singleton.h"
#include "BaconBox/FileSystem/File.h"
#include <string>

namespace BaconBox {
	/**
	 * Wraps access to an implementation of the BaconBox VFS.
	 * This is basically a static proxy class.
	 */
	class FileSystem {
	public:
		/**
		 * Opens a File on the VFS. Returns a File, but is actually of a
		 * specialized type for the specific VFS.
		 * @param path Path to open.
		 * @param mode Mode to open, "r", "w" or "a". Defaults to "r".
		 * @return The File pointer of the opened file.
		 */
		static File* open(const std::string& path, const std::string& mode = "r");
		/**
		 * Checks the file or path asked exists on the VFS.
		 * @param path Path to check for.
		 * @return Whether it exists or not.
		 */
		static bool exists(const std::string& path);
		/**
		 * Mounts a "thing" to the VFS.
		 * The "thing" is dependent on the VFS backend.
		 *
		 * Most VFS allow mounting multiple read-only "things".
		 * Some (most?) VFS will not allow multiple write "things".
		 * In that case, the second call will /change/ the writing directory.
		 *
		 * @param what The "thing" to mount.
		 * @param where Where to mount it (defaults to /).
		 * @param append Whether it is a writable directory.
		 * @param append Priority, defaults to first. Set to true for last.
		 * @return Whether it succeeded or not.
		 */
		static bool mount(const std::string& what, const std::string& where = "/", const bool write = false, const bool append = false);
		
		/**
		 * Mounts in relationship to the platform's default resource path.
		 * This uses a platform-dependent method to mount the asked resource.
		 */
		static bool mountFromResources(const std::string& what, const std::string& where = "/");
		
		/**
		 * Gets a platform-specific resource base folder.
		 * This is mostly relevant for platforms where the application is *installed* in
		 * a location that is discoverable through various methods.
		 */
		static std::string getResourcePath();

		/**
		 * Mounts the default platform-specific save path.
		 * If you need a specific save path, mount it manually.
		 *
		 * @param where Where to mount it (defaults to /Save/).
		 * @return Whether it succeeded or not.
		 */
		static bool mountDefaultSavePath(const std::string& where = "/Save");

		/// Gets the platform-specific save path.
		static std::string getPlatformSavePath();
	private:
		FileSystem();
	};
}
#endif // FILESYSTEM_H
