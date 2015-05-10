#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "BaconBox/Core/Singleton.h"
#include "BaconBox/FileSystem/File.h"
#include <string>

namespace BaconBox {
	/**
	 * Wraps access to a filesystem-like thing.
	 */
	class FileSystem : public Singleton {
		BB_SINGLETON_DECL(FileSystem);
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
		 * @param what The "thing" to mount.
		 * @param where Where to mount it (defaults to /).
		 * @param append Priority, defaults to first. Set to true for last.
		 * @return Whether it succeeded or not.
		 */
		static bool mount(const std::string& what, const std::string& where = "/", const bool append = false);
	protected:
		File* _open(const std::string& path, const std::string& mode);
		bool _exists(const std::string& path);
		bool _mount(const std::string& what, const std::string& where, const bool append);
	private:
		FileSystem();
	};
}
#endif // FILESYSTEM_H
