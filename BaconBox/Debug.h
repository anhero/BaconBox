#ifndef BB_DEBUG_H
#define BB_DEBUG_H
#include "BaconBox/Core/Singleton.h"
#include "BaconBox/Core/Engine.h"

namespace BaconBox {
    class Debug : public Singleton {
		BB_SINGLETON_DECL(Debug);
	public:

		Debug();

		bool trackMovieClip;

		void createMovieClip(const std::string &key);
		void destroyMovieClip(const std::string &key);
		void printMovieClips(int minValue = 0);
	private:
		std::map<std::string, int> movieClips;

	};
}

#endif


