#include "EntityFactory.h"

#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/ColorFilter.h"
#include "BaconBox/Components/MeshDriverRenderer.h"
#include "BaconBox/Components/Texture.h"
#include "BaconBox/ResourceManager.h"
#include "BaconBox/Display/TextureInformation.h"

#ifdef BB_FLASH_PLATEFORM
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
	#include "BaconBox/Helper/Flash/FlashHelper.h"

#endif	



namespace BaconBox {
	
	MovieClipEntity * EntityFactory::getMovieClipEntity(const std::string & key){
		#ifdef BB_FLASH_PLATEFORM	
			AS3::local::var mc =  FlashHelper::construct(key);
			AS3::local::var entity = FlashHelper::getProperty(mc, "entity");
			AS3::local::var entityPointerAS3 = FlashHelper::getProperty(entity, "swigCPtr");
			MovieClipEntity * entityPointer = (MovieClipEntity*)int_valueOf(entityPointerAS3);
			return entityPointer;
		#endif	  
	}
	
	Entity *EntityFactory::getTexturedEntity(TexturePointer texture) {
		Entity *result = NULL;
		
		if (texture.pointer) {
			result = new Entity();
			
			result->addComponent(new Transform());
			
			Vector2 size(static_cast<float>(texture.pointer->imageWidth), static_cast<float>(texture.pointer->imageHeight));
			
			Vector2 poweredSize(static_cast<float>(texture.pointer->poweredWidth), static_cast<float>(texture.pointer->poweredHeight));
			
			Mesh *mesh = new Mesh();

			mesh->getVertices().resize(4);
			
			mesh->getVertices()[1].x = size.x;
			mesh->getVertices()[2].y = size.y;
			mesh->getVertices()[3] = size;
			
			result->addComponent(mesh);
			
			result->addComponent(new ColorFilter(Color::WHITE));
			
			Texture *textureComponent = new Texture();
			
			textureComponent->setTexture(texture.pointer);
			
			textureComponent->getTextureCoordinates().resize(4);
			textureComponent->getTextureCoordinates()[1].x = size.x / poweredSize.x;
			textureComponent->getTextureCoordinates()[2].y = size.y / poweredSize.y;
			textureComponent->getTextureCoordinates()[3] = size.getCoordinatesDivision(poweredSize);
			
			result->addComponent(textureComponent);
			
			result->addComponent(new MeshDriverRenderer(RenderMode::SHAPE | RenderMode::COLOR | RenderMode::TEXTURE));
		}
		return result;
	}
}
