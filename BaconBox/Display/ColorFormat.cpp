#include "ColorFormat.h"

using namespace BaconBox;

ColorFormat::type ColorFormat::colorFormatFromString(const std::string & format){
	ColorFormat::type colorFormat = ColorFormat::NONE;
	if(format == "RGBA"){
		colorFormat = ColorFormat::RGBA;
	}
	else if(format == "RGBA4"){
		colorFormat = ColorFormat::RGBA4;
	}
	if(format == "ALPHA"){
		colorFormat = ColorFormat::ALPHA;
	}
	return colorFormat;
}