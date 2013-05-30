#include "Symbol.h"

namespace BaconBox {
	Symbol::Symbol():subTex(NULL), isTexture(false), isTextField(false), frameCount(1), color(Color::WHITE), blend(true){}
	Symbol::Part::Part(): symbol(NULL){}
}
