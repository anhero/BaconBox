#ifndef BB_Scene_H
#define BB_Scene_H

#include <vector>
#include <string>

namespace BaconBox {
	struct Scene {
	public:
		Scene();
		
		Scene(const std::vector<std::string> &newLabels, const std::string &newName, int newNbFrames);
		
		Scene(const Scene &src);
		
		Scene &operator=(const Scene &src);
		
		std::vector<std::string> labels;
		
		std::string name;
		
		int nbFrames;
	};
}

#endif /* defined(BB_Scene_H) */

