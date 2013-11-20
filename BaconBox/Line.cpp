#include "Line.h"
#include <string>
#include "BaconBox/Components/Texture.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/MeshDriverRenderer.h"
#include "BaconBox/ResourceManager.h"
#ifdef BB_FLASH_PLATFORM

#else
#include "BaconBox/Components/DefaultLineComponent.h"
#endif

namespace BaconBox {

    BB_ID_IMPL(Line);

	Line::Line(const std::string & patternKey): MovieClipEntity(), LineComponentProxy(this){
#ifdef BB_FLASH_PLATFORM
		
#else
		addComponent(new Mesh());
		Texture * texture = new Texture();
		SubTextureInfo * subTex = ResourceManager::getSubTexture(patternKey);
		texture->setTexture(subTex->textureInfo);
		addComponent(texture);
		setLineComponent(new DefaultLineComponent(subTex));
		addComponent(new MeshDriverRenderer(RenderMode::SHAPE | RenderMode::COLOR  | RenderMode::TEXTURE| RenderMode::COLOR_TRANSORMED | RenderMode::BLENDED, 4, 1));
		

#endif
	}

	Line::Line(const Line& src) : MovieClipEntity(), LineComponentProxy(this){

	}
	
	Line::~Line() {
	}

	Line &Line::operator=(const Line &src) {
		this->MovieClipEntity::operator=(src);
		
		if (this != &src) {
		}
		
		return *this;
	}


}
