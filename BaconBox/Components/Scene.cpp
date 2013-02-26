#include "Scene.h"

namespace BaconBox {
	Scene::Scene() : labels(), name(), nbFrames(0) {
	}
	
	Scene::Scene(const std::vector<std::string> &newLabels, const std::string &newName, int newNbFrames) : labels(newLabels), name(newName), nbFrames(newNbFrames) {
	}
	
	Scene::Scene(const Scene &src) : labels(src.labels), name(src.name), nbFrames(src.nbFrames) {
	}
	
	Scene &Scene::operator=(const Scene &src) {
		if (this != &src) {
			this->labels = src.labels;
			this->name = src.name;
			this->nbFrames = src.nbFrames;
		}
		
		return *this;
	}
}
