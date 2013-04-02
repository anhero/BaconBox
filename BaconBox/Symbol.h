#ifndef BB_SYMBOL_H
#define BB_SYMBOL_H

#include "Display/SubTextureInfo.h"
#include <map>
#include <set>
#include "BaconBox/Matrix.h"

namespace BaconBox {
    struct Symbol{
	typedef std::map<int, Matrix> MatrixByFrame;
	typedef std::pair<MatrixByFrame,Symbol*> SymbolPart;
	typedef std::vector<std::pair<std::string, std::pair<std::set<int>, SymbolPart> > > Parts;
	Symbol();
	std::set<int> frame;
	int frameCount;
	std::string key;
	SubTextureInfo * subTex;
	bool isTexture;
	Symbol * symbol;
	Parts parts;
	Vector2 registrationPoint;
    };
    
	
    
}

#endif


