#ifndef BASEVFS_H
#define BASEVFS_H

#include "BaconBox/Core/Singleton.h"
#include "BaconBox/FileSystem/File.h"
#include <string>

namespace BaconBox {
	/**
	 * Base BaconBox VFS interface.
	 */
	class BaseVFS : public Singleton {
	public:
		/**
		 * Opens a File on the VFS. Returns a File, but is actually of a
		 * specialized type for the specific VFS.
		 * @param path Path to open.
		 * @param mode Mode to open, "r", "w" or "a". Defaults to "r".
		 * @return The File pointer of the opened file.
		 */
		virtual File* open(const std::string& path, const std::string& mode) = 0;
		/**
		 * Checks the file or path asked exists on the VFS.
		 * @param path Path to check for.
		 * @return Whether it exists or not.
		 */
		virtual bool exists(const std::string& path) = 0;
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
		virtual bool mount(const std::string& what, const std::string& where = "/", const bool write = false, const bool append = false) = 0;

	protected:
		BaseVFS();
	};
}
#endif // BASEVFS_H
