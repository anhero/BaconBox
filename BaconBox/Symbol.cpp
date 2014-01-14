#include "Symbol.h"

namespace BaconBox {
	Symbol::Symbol():subTex(NULL), isTexture(false), isTextField(false), frameCount(1), scale(1.0f), color(Color::WHITE), blend(true){}
	Symbol::Part::Part(): symbol(NULL){}
	
	bool Symbol::hasLabel(const std::string & labelName){
		return label.find(labelName) != label.end();
	}

}
