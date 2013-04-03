#ifndef BB_SYMBOL_H
#define BB_SYMBOL_H

#include "Display/SubTextureInfo.h"
#include <map>
#include <set>
#include "BaconBox/Matrix.h"

namespace BaconBox {
    struct Symbol{
	struct Part{
	    Part();
	    typedef std::map<int, Matrix> MatrixByFrame;
	    std::string name;
	    MatrixByFrame matrices;
	    std::set<int> frames;
	    Symbol * symbol;
	};
	Symbol();
	int frameCount;
	std::string key;
	SubTextureInfo * subTex;
	bool isTexture;
//	Symbol * symbol;
	std::vector<Part> parts;
	Vector2 registrationPoint;
	
	
    };
}

#endif


