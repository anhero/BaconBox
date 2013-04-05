#ifndef BB_SYMBOL_H
#define BB_SYMBOL_H

#include "Display/SubTextureInfo.h"
#include <set>
#include <list>

#include "BaconBox/Matrix.h"

namespace BaconBox {
    struct Symbol{
	struct Part{
//	    struct compare
//	    {
//		bool operator() (const Part & a, const Part & b)
//		{
//		    return a.layerIndex < b.layerIndex; 
//		}
//		bool operator() (const Part & a, const Part & b)
//		{
//		    return a.layerIndex < b.layerIndex; 
//		}
//	    };
		
	    Part();
	    typedef std::map<int, Matrix> MatrixByFrame;
	    typedef std::map<int, int> IndexByFrame;
	    IndexByFrame indexByFrame;
	    std::string name;
	    MatrixByFrame matrices;
	    Symbol * symbol;
	};
	Symbol();
	int frameCount;
	std::string key;
	SubTextureInfo * subTex;
	bool isTexture;
//	Symbol * symbol;
	std::list<Part> parts;
	Vector2 registrationPoint;
	
	
    };
}

#endif


