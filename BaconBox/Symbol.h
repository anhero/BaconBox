

#ifndef BB_SYMBOL_H
#define BB_SYMBOL_H

#include "Display/SubTextureInfo.h"
#include <map>
#include <set>
#include "BaconBox/Matrix.h"

namespace BaconBox {
    struct Symbol{
	Symbol();
	std::set<int> frame;
	std::string key;
	SubTextureInfo * subTex;
	bool isTexture;
	std::map<int, Matrix> frameMatrices;
	Symbol * symbol;
	std::vector<std::pair<std::string,Symbol*> > parts;

	Vector2 registrationPoint;
    };
    
	
    
}

#endif
