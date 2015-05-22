#ifndef PhysFSVFS_H
#define PhysFSVFS_H

#include "BaconBox/FileSystem/BaseVFS.h"
namespace BaconBox {

	/**
	 * Implementation of the BaseVFS for PhysicsFS.
	 */
	class PhysFSVFS : public BaseVFS {
		BB_SINGLETON_DECL(PhysFSVFS)
	public:
		virtual File* open(const std::string& path, const std::string& mode);
		virtual bool exists(const std::string& path);
		virtual bool mount(const std::string& what, const std::string& where = "/", const bool write = false, const bool append = false);
		virtual const std::string getBaseDir();
		PhysFSVFS();
	};

}

#endif // PhysFSVFS_H
