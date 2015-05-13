#ifndef SYSTEMFS_H
#define SYSTEMFS_H

#include <string>

// TODO : Inherit from a BaseVFS interface.
namespace BaconBox {

	/**
	 * Will eventually be a complete BaconBox VFS abstraction of the system's filesystem,
	 * but for now, a place to store static methods touching the system's filesystem.
	 *
	 * For convenience, we're supplying aliases that are unix-ish like in appearance.
	 */
	class SystemFS {
	public:
		/// Verifies that a path exists on the system's filesystem.
		static bool exists(const std::string &path);
		/// Verifies that a path is a directory on the system's filesystem.
		static bool isDirectory(const std::string &path);
		/// Creates a directory on the system's filesystem (mkdir).
		static bool createDirectory(const std::string &path);
		/// Creates a directory tree on the system's filesystem (mkdir -p).
		static bool createDirectoryTree(const std::string &path);

		/// Deletes a directory (rm -rf dir/)
		static bool removeDirectoryTree(const std::string &path);

		/// Alias for createDirectory
		static bool mkdir(const std::string &path);
		/// Alias for createDirectoryTree
		static bool mkdir_p(const std::string &path);
		// /// Alias for either rm or removeDirectoryTree
		// TODO: Make a function that calls wither removeFile or removeDirectoryTree.
		// static bool rm_r(const std::string &path);
	protected:
		SystemFS();
	};
}

#endif // SYSTEMFS_H
