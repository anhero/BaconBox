

#ifndef BB_SYMBOL_H
#define BB_SYMBOL_H

#include "Display/SubTextureInfo.h"
#include <map>
#include <set>


namespace BaconBox {
    class Matrix;
    struct Symbol{
	SymbolPart();
	std::set<int> frame;
	std::string name;
	SubTextureInfo * subTex;
	int index;
	std::map<int, Matrix> frameMatrices;
	Symbol * symbol;
	std::map<int,Symbol*> parts;

	Vector2 registrationPoint;
    };
    
	
    
}

#endif
