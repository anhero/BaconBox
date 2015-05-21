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
		 * Mounts (as read-only) a path to the VFS. In the end, this is platform-dependent.
		 *
		 * @param what The "thing" to mount.
		 * @param where Where to mount it (defaults to /).
		 * @param append Priority, defaults to first. Set to true for last.
		 * @return Whether it succeeded or not.
		 */
		static bool mount(const std::string& what, const std::string& where = "/", const bool append = false);

		/**
		 * Mounts a "thing" to the VFS.
		 * The "thing" is dependent on the VFS backend.
		 *
		 * @param what The "thing" to mount.
		 * @param where Where to mount it (defaults to /).
		 * @param write Whether it is a writable directory.
		 * @param append Priority, defaults to first. Set to true for last.
		 * @return Whether it succeeded or not.
		 */
		static bool rawMount(const std::string& what, const std::string& where = "/", const bool write = false, const bool append = false);

		/**
		 * Gets a platform-specific resource base folder.
		 * This is mostly relevant for platforms where the application is *installed* in
		 * a location that is discoverable through various methods.
		 */
		static std::string getBaseDir();

		/**
		 * Mounts the default platform-specific save path.
		 * If you need a specific save path, mount it manually.
		 *
		 * @param where Where to mount it (defaults to /Save/).
		 * @return Whether it succeeded or not.
		 */
		static bool mountDefaultSavePath(const std::string& where = "/Save");

		/**
		 * Configure the VFS to use the CWD as the base directory for mounting
		 * instead of using the platform-dependent base directory.
		 *
		 * @param useCWD Whether to use the CWD as baseDir.
		 */
		static void useCWD(const bool useCWD = true);

		/// Gets the platform-specific save path.
		static std::string getPlatformSavePath();

		static bool use_cwd;
	private:
		FileSystem();
	};
}
#endif // FILESYSTEM_H
