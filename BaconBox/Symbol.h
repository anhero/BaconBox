#ifndef BB_SYMBOL_H
#define BB_SYMBOL_H

#include "Display/SubTextureInfo.h"
#include <set>
#include <list>

#include "BaconBox/Matrix2D.h"
#include "BaconBox/ColorMatrix.h"

#include "BaconBox/Display/Color.h"
#include "BaconBox/Display/Text/TextAlignment.h"

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
	    typedef std::map<int, Matrix2D> MatrixByFrame;
	    typedef std::map<int, ColorMatrix> ColorMatrixByFrame;
	    typedef std::map<int, int> IndexByFrame;
	    IndexByFrame indexByFrame;
	    std::string name;
	    MatrixByFrame matrices;
	    ColorMatrixByFrame colorMatrices;
	    Symbol * symbol;
	};
	Symbol();
	int frameCount;
	std::string key;
	std::string textureKey;
	SubTextureInfo * subTex;
	bool isTexture;
	bool isTextField;
		bool blend;
		std::string font;
		std::string text;
		int textFieldWidth;
		int textFieldHeight;
		int fontSize;
		float scale;
		TextAlignment::type alignment;
	    Color color;
//	Symbol * symbol;
	std::list<Part> parts;
	Vector2 registrationPoint;
	std::map<std::string, std::pair<int, int> > label;


    };
}

#endif


