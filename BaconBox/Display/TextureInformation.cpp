#include "BaconBox/Display/TextureInformation.h"

#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Helper/MathHelper.h"

namespace BaconBox {

#if defined (BB_OPENGL) || defined (BB_OPENGLES)
	TextureInformation::TextureInformation(): textureId(0), colorFormat(ColorFormat::RGBA),
		poweredWidth(0), poweredHeight(0), imageWidth(0), imageHeight(0), path("") {
	}

	TextureInformation::TextureInformation(unsigned int newTextureId,
	                                       unsigned int newImageWidth,
	                                       unsigned int newImageHeight,
						const std::string & path): textureId(newTextureId),
		colorFormat(ColorFormat::RGBA),
		poweredWidth(MathHelper::nextPowerOf2(newImageWidth)),
		poweredHeight(MathHelper::nextPowerOf2(newImageHeight)),
		imageWidth(newImageWidth), imageHeight(newImageHeight), path(path){
	}
#else
	TextureInformation::TextureInformation(): poweredWidth(0), poweredHeight(0), imageWidth(0),
		imageHeight(0), colorFormat(ColorFormat::RGBA), path("") {
	}
	TextureInformation::TextureInformation(unsigned int newImageWidth,
	                                       unsigned int newImageHeight,
						const std::string & path): poweredWidth(MathHelper::nextPowerOf2(newImageWidth)),
		poweredHeight(MathHelper::nextPowerOf2(newImageHeight)),
		imageWidth(newImageWidth), imageHeight(newImageHeight),
                colorFormat(ColorFormat::RGBA), path(path){
	}
#endif

	std::ostream &operator<<(std::ostream &output, const TextureInformation &t) {
		output << "{";
#if defined (BB_OPENGL) || defined (BB_OPENGLES)
		output << "textureId: " << t.textureId << ", ";
#endif
		output << "poweredWidth: " << t.poweredWidth << ", poweredHeight: " <<
		       t.poweredHeight << ", imageWidth: " << t.poweredWidth << ", imageHeight: " <<
		       t.poweredHeight << ", path: " << t.path << "}";
		return output;
	}
}
