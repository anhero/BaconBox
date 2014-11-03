#include "Debug.h"
#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Console.h"
using namespace BaconBox;

BB_SINGLETON_IMPL(Debug);

Debug::Debug() : Singleton(){
	trackMovieClip = false;
}

void Debug::createMovieClip(const std::string &key){
	#ifdef BB_DEBUG
		if(trackMovieClip){
			movieClips[key]++;
		}
	#endif
}

void Debug::destroyMovieClip(const std::string &key){
	#ifdef BB_DEBUG
		if(trackMovieClip){
			movieClips[key]--;
		}
	#endif
}


void Debug::printMovieClips(int minValue){
	std::map<std::string, int>::iterator i;
	std::multimap<int, const std::string*> sortedMCs;
	for(i = movieClips.begin(); i != movieClips.end(); i++){
		sortedMCs.insert(std::pair<int, const std::string*>(i->second, &(i->first)));
	}	
	int total = 0;
	int others = 0;
	std::multimap<int, const std::string*>::reverse_iterator j;
	for(j = sortedMCs.rbegin(); j != sortedMCs.rend(); j++){
		if(j->first > minValue){
			PRLN("Key: " <<  *(j->second) << " - " << j->first);
		}
		else{
			others += j->first;
		}
		total += j->first;
	}
	if(others > 0) {
		PRLN("Others - " << others);
	}
	PRLN("Total: " << total);
}
