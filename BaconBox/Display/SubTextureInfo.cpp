#include "BaconBox/Display/SubTextureInfo.h"

namespace BaconBox {

SubTextureInfo::SubTextureInfo(TextureInformation * textureInfo, Vector2 position, Vector2 size): textureInfo(textureInfo), position(position), size(size){
}
	
	SubTextureInfo::SubTextureInfo(const SubTextureInfo& src):textureInfo(src.textureInfo), position(src.position), size(src.size){}

	
	Vector2 SubTextureInfo::getTextureCoordinatePosition(){
		return getTopLeftCoord();
	}
	
	Vector2 SubTextureInfo::getTextureCoordinateSize(){
		return getDownRightCoord() - getTextureCoordinatePosition();
	}
	
	Vector2 SubTextureInfo::getTopLeftCoord(){
		Vector2 coord(position.x/textureInfo->poweredWidth, position.y/textureInfo->poweredHeight);
		return coord;
	}
	
	Vector2 SubTextureInfo::getTopRightCoord(){
		Vector2 coord((position.x + size.x)/textureInfo->poweredWidth, (position.y)/textureInfo->poweredHeight);
		return coord;
	}
	
	Vector2 SubTextureInfo::getDownLeftCoord(){
		Vector2 coord((position.x)/textureInfo->poweredWidth, (position.y + size.y)/textureInfo->poweredHeight);
		return coord;
	}
	
	Vector2 SubTextureInfo::getDownRightCoord(){
		Vector2 coord((position.x + size.x)/textureInfo->poweredWidth, (position.y + size.y)/textureInfo->poweredHeight);
		return coord;
	}
}
