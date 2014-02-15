#include "BaconBox/Helper/Random.h"

#include "BaconBox/PlatformFlagger.h"

#include <cstdlib>
#include <ctime>
namespace BaconBox {
	double Random::D_RAND_MAX = static_cast<double>(RAND_MAX);
	bool Random::initialized = false;

	int Random::getRandomInteger(int min, int max) {
		if (!initialized) {
			init();
		}

#ifdef BB_IPHONE_PLATFORM
		return (arc4random() % ((max + 1) - min)) + min;
#else
		return (rand() % ((max + 1) - min)) + min;
#endif
		//return min + (int) ((double) rand () * (max - min + 1)
		//					/ ((unsigned) RAND_MAX + 1));
	}

	bool Random::getRandomBool() {
		if (!initialized) {
			init();
		}

#ifdef BB_IPHONE_PLATFORM
		return arc4random() % 2;
#else
		return rand() % 2;
#endif
	}

	Vector2 Random::getRandomVector2(const Vector2 & min, const Vector2 & max, bool keepRatio){
		Vector2 randomVec;
		randomVec.x = Random::getRandomFloat(min.x, max.x);
		if (keepRatio) {
			randomVec.y = min.y/min.x * randomVec.x;
		}
		else{
			randomVec.y = Random::getRandomFloat(min.y, max.y);

		}
		return randomVec;
	}

	double Random::getRandomDouble(double min, double max) {
		if (!initialized) {
			init();
		}

		return (static_cast<double>(rand()) / Random::D_RAND_MAX) * (max - min) + min;
	}

	float Random::getRandomFloat(float min, float max) {
		if (!initialized) {
			init();
		}

		return (static_cast<float>(rand()) / Random::D_RAND_MAX) * (max - min) + min;
	}

	void Random::init() {
		srand(static_cast<unsigned int>(time(NULL)));
		initialized = true;
	}
}