

#ifndef BB_SYMBOLPART_H
#define BB_SYMBOLPART_H

#include "Display/SubTextureInfo.h"






namespace BaconBox {
    struct Symbol;
    struct SymbolPart{
	std::set<int> range;
	std::string name;
	SubTextureInfo * subTex;
	int index;
	std::map<int, Matrix> frameMatrices;
	Symbol * symbol;
    };
    
	
    
}

#endif
