#include "EntityFactory.h"

#include "BaconBox/PlatformFlagger.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Components/Mesh.h"
#include "BaconBox/Components/ColorTransform.h"
#include "BaconBox/Components/StandardRenderer/MeshDriverRenderer.h"
#include "BaconBox/Components/DefaultEntityContainer.h"
#include "BaconBox/Components/DefaultTimeline.h"

#include "BaconBox/Components/Texture.h"
#include "BaconBox/ResourceManager.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Console.h"
#include "Components/DefaultEntityContainer.h"
#include "Components/DefaultMatrix.h"
#include "Core/Engine.h"

#include "BaconBox/Helper/ShapeFactory.h"

#ifdef BB_FLASH_PLATFORM
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
#include "BaconBox/Helper/Flash/FlashHelper.h"
#else
#include "BaconBox/Display/StandardRenderer/TexturePointer.h"

#endif

#include <BaconBox/Console.h>
#include <BaconBox/Display/Text/Font.h>

#include <BaconBox/Console.h>
#include "BaconBox/LocalizationManager.h"

namespace BaconBox {
	
	EntityFactory::EntityFactory():movieClipPool(0){
		
		
	}
	
    void EntityFactory::claimMovieClipEntity(MovieClipEntity * mc){
        getInstance().internalClaimMovieClipEntity(mc);
    }
    
    void EntityFactory::internalClaimMovieClipEntity(MovieClipEntity * mc){
        delete mc;
    }

	
	void EntityFactory::initMovieClipPool(int size){
		getInstance().movieClipPool.setNbAvailableObjects(size);
	}
	
	MovieClipEntity *EntityFactory::getMovieClipEntity(const std::string &key, bool autoPlay) {
		MovieClipEntity * temp = getInstance().internalGetMovieClipEntity(key, autoPlay);
		if (temp && temp->getSymbol() == NULL){
			ResourceManager::addSymbol(key);
		}
		return temp; 
	}
	MovieClipEntity *EntityFactory::getMovieClipEntity() {
		MovieClipEntity * temp = getInstance().internalGetMovieClipEntity();
		if(temp->getSymbol() == NULL){
            Symbol * symbol = ResourceManager::getSymbol("");
            if (!symbol) {
                symbol = ResourceManager::addSymbol("");
            }
			temp->setSymbol(symbol);
		}
		return temp; 
	}
	
	MovieClipEntity *EntityFactory::internalGetMovieClipEntity() {
		#ifdef BB_FLASH_PLATFORM
			AS3::local::var mc =  FlashHelper::construct("BaconBox.EntityWrapper.EntityHolderMovieClip");
			return FlashHelper::getMCEntityFromMC(mc);
		#else	
			return movieClipPool.create();
		#endif
	}
	
	EntityFactory &EntityFactory::getInstance(){
		static EntityFactory instance;
		return instance;
	}
	
	MovieClipEntity *EntityFactory::internalGetMovieClipEntity(const std::string &key, bool autoPlay) {
#ifdef BB_DEBUG
		try{
#endif
#ifdef BB_FLASH_PLATFORM
			AS3::local::var mc =  FlashHelper::construct(key);
			return FlashHelper::getMCEntityFromMC(mc);
			
#else
			MovieClipEntity * entity;
			Symbol * symbol = ResourceManager::getSymbol(key);
			if(symbol){
				entity = getMovieClipEntityFromSymbol(symbol, autoPlay);
			}
			else{
				entity = getMovieClipEntityFromSubTexture(ResourceManager::getSubTexture(key));
			}
#ifdef BB_DEBUG
			if(!entity){
				PRLN("[Warning] EntityFactory::getMovieClipEntity() can't return entity with key: " << key);
			}
#endif
			return entity;
			//		SubTextureInfo* subTex = ResourceManager::getSubTexture(key);
			//		return getMovieClipEntityFromSubTexture(subTex);
			
			
#endif
			
#ifdef BB_DEBUG
		}
		catch(...){
			Console__error("Error in EntityFactory::getMovieClipEntity with key: " << key);
			throw;
		}
#endif
	}
	
#if  defined(BB_FLASH_PLATFORM)
	TextEntity * EntityFactory::getTextEntity(const std::string &key){
		AS3::local::var mc =  FlashHelper::construct(key);
		return reinterpret_cast<TextEntity*>(FlashHelper::getMCEntityFromMC(mc));
	}
#else
	
	MovieClipEntity *EntityFactory::getMovieClipEntityFromSymbol(Symbol* symbol, bool autoPlay){
		if (symbol == NULL) {
			Console__error("FATAL : symbol is NULL");
			return NULL;
		}
		MovieClipEntity * entity = NULL;
	    if(symbol->isTexture){
			if(!symbol->subTex->textureInfo || symbol->subTex->textureInfo->textureId == -1){
				std::string textureKey = symbol->textureKey;
				TextureInformation * textureInfo = NULL;
				if(ResourceManager::isLoadedTexture(textureKey)){
					textureInfo = ResourceManager::getTexture(textureKey);
				}
				else{
					textureInfo = ResourceManager::loadTexture(symbol->textureKey);
				}
				symbol->subTex = ResourceManager::getSubTexture(symbol->key);
				symbol->subTex->textureInfo = textureInfo;
			}
			float scale  = 1.0f/symbol->scale;
			entity = getMovieClipEntityFromSubTexture(symbol->subTex, symbol->registrationPoint , symbol->blend, scale);
	    }
	    else{
			if(symbol->isTextField){
				Font * font = ResourceManager::getFont(symbol->font,  symbol->fontSize);
				if(font == NULL) Console::error("Missing font " + symbol->font);
				TextEntity * tf = font->getTextEntity();
				LocalizationManager::getInstance().addTextEntity(tf);
				bool noTextFound = false;
				std::map<std::string, std::string> * translation = LocalizationManager::getInstance().getCurrentTranslations();
				if(translation){
					std::map<std::string, std::string>::iterator found = translation->find(symbol->key);
					if(found != translation->end()){
						tf->setText(found->second);
					}
					else{
						noTextFound = true;
					}
				}
				else{
					noTextFound = true;
				}
				
				if(noTextFound){
					tf->setText(symbol->text);
				}
				
				tf->setAlignment(symbol->alignment);
				tf->setPixelSize(symbol->fontSize);
				tf->setSize(Vector2(symbol->textFieldWidth, symbol->textFieldHeight));
				entity = tf;
                entity->setColor(symbol->color);
				// Force the update of the text to make it refresh
				// itself with internalReset*()
				tf->update();
				
			}
			else{
				entity = movieClipPool.create();
			}
			DefaultEntityContainer * container = reinterpret_cast<DefaultEntityContainer*>(entity->getComponent(DefaultEntityContainer::ID));
			DefaultTimeline * timeline = reinterpret_cast<DefaultTimeline*>(entity->getComponent(DefaultTimeline::ID));
			timeline->setNbFrames(symbol->frameCount);
			std::map<int, std::map <int, Symbol::Part*> > orderedPart;
			for(std::list<Symbol::Part>::iterator i = symbol->parts.begin();
				i != symbol->parts.end(); i++){
				for(std::map<int,int>::iterator j = i->indexByFrame.begin(); j != i->indexByFrame.end(); j++){
					orderedPart[j->first][j->second] = &(*i);
				}
			}
			std::map<std::string, MovieClipEntity*> childByName;


			for(std::map<int, std::map <int, Symbol::Part*> >::iterator i = orderedPart.begin();
				i != orderedPart.end(); i++){
				entity->gotoAndStop(i->first);
				for(std::map <int, Symbol::Part*>::iterator j = i->second.begin(); j != i->second.end(); j++){
					MovieClipEntity * childEntity = NULL;
					std::map<std::string, MovieClipEntity*>::iterator currentMovieClip = childByName.find(j->second->name);
					if(currentMovieClip == childByName.end()){
						if (j->second->symbol == NULL) {
							Console__error("FATAL : Symbol '" << j->second->name <<
									"' in " << entity->getEntityName() << " '" <<
									symbol->key << "' is not found.");
						}
						childEntity = getMovieClipEntityFromSymbol(j->second->symbol, autoPlay);
						childByName[j->second->name] = childEntity;
					}
					else{
						childEntity = currentMovieClip->second;
					}
					childEntity->setName(j->second->name);
					reinterpret_cast<DefaultMatrix*>(childEntity->getMatrixComponent())->matrixByParentFrame = &j->second->matrices;
					reinterpret_cast<DefaultColorTransform*>(childEntity->getColorTransform())->matrixByParentFrame = &j->second->colorMatrices;
					
					container->addChildToCurrentFrame(childEntity);
				}
			}

			if (symbol->autoPlay) {
				autoPlay = true;
			}

			if(autoPlay){
				entity->gotoAndPlay(0);
			}
			else{
				entity->gotoAndStop(0);
			}
			
	    }
		entity->setSymbol(symbol);
		if(!entity) Console__error("Error calling EntityFactory::getMovieClipEntityFromSymbol with symbol " + symbol->key);
		return entity;
	}
	
	MovieClipEntity *EntityFactory::getMovieClipEntityFromSubTexture(SubTextureInfo* subTex, const Vector2 & origin, bool blend, float scale){
	    MovieClipEntity *result = NULL;
		if (subTex) {
			result = movieClipPool.create();
			
			Mesh *mesh = new Mesh();
			
			
			mesh->getPreTransformVertices().resize(4);
			
			
			mesh->getPreTransformVertices()[1].x = subTex->size.x * scale;
			mesh->getPreTransformVertices()[2].y = subTex->size.y * scale;
			mesh->getPreTransformVertices()[3] = subTex->size * scale;
			
			mesh->getPreTransformVertices().move(origin.x * scale, origin.y * scale);
			
			result->addComponent(mesh);
			
			Texture *textureComponent = new Texture();
			
			textureComponent->setTexture(subTex->textureInfo);
			
			textureComponent->getTextureCoordinates().resize(4);
			textureComponent->getTextureCoordinates()[0] = subTex->getTopLeftCoord();
			textureComponent->getTextureCoordinates()[1] = subTex->getTopRightCoord();
			textureComponent->getTextureCoordinates()[2] = subTex->getDownLeftCoord();
			textureComponent->getTextureCoordinates()[3] = subTex->getDownRightCoord();
			result->addComponent(textureComponent);
			
			result->addComponent(new MeshDriverRenderer(RenderMode::SHAPE | RenderMode::COLOR | RenderMode::TEXTURE | RenderMode::COLOR_TRANSORMED | (blend ? RenderMode::BLENDED : RenderMode::NONE)));

			// Create a symbol for the subtexture if none exists.
			Symbol * symbol = ResourceManager::getSymbol(subTex->textureInfo->key);
			if (!symbol) {
				symbol = ResourceManager::addSymbol(subTex->textureInfo->key);
				symbol->subTex = subTex;
				symbol->isTexture = true;
				symbol->textureKey = subTex->textureInfo->key;
			}
			result->setSymbol(symbol);

		}
		
		return result;
	}

	MovieClipEntity *EntityFactory::getShapeRectangle(float w, float h, const Vector2 & origin, bool blend, float scale){
		return getInstance().internalGetShapeRectangle(w, h, origin, blend, scale);
	}

	MovieClipEntity *EntityFactory::internalGetShapeRectangle(float w, float h, const Vector2 & origin, bool blend, float scale){
		MovieClipEntity *result = movieClipPool.create();
		Mesh *mesh = new Mesh();

		// Mesh vertices
		//
		// 0_____1
		// |     |
		// |     |
		// |_____|
		// 2     3
		//
		
		mesh->getPreTransformVertices().resize(4);
		mesh->getPreTransformVertices()[1].x = w * scale;
		mesh->getPreTransformVertices()[2].y = h * scale;
		mesh->getPreTransformVertices()[3].x = w * scale;
		mesh->getPreTransformVertices()[3].y = h * scale;
		mesh->getPreTransformVertices().move(origin.x * scale, origin.y * scale);
		
		result->addComponent(mesh);
		
		result->addComponent(new MeshDriverRenderer(
								 RenderMode::SHAPE | RenderMode::COLOR |
								 RenderMode::COLOR_TRANSORMED | (blend ? RenderMode::BLENDED : RenderMode::NONE)
								 ));
		
		return result;
	}

	MovieClipEntity *EntityFactory::getRegularPolygon(unsigned int nbSides, float sideLength, bool blend, float scale){
		return getInstance().internalGetRegularPolygon(nbSides, sideLength, blend, scale);
	}

	MovieClipEntity *EntityFactory::internalGetRegularPolygon(unsigned int nbSides, float sideLength, bool blend, float scale){
		// It is invalid to ask for les than three sides!
		if (! (sideLength > 0 && nbSides >= 3) ) {
			return NULL;
		}

		MovieClipEntity *result = movieClipPool.create();
		Mesh *mesh = new Mesh();

		// Prepare the mesh for the right amount of vertices.
		mesh->getPreTransformVertices().resize(nbSides);

		// Send the mesh to the ShapeFactory.
		ShapeFactory::createRegularPolygon(nbSides, sideLength, Vector2(), &(mesh->getPreTransformVertices()));

		// Move the origin to the middle.
		// If that's not where you want it, move it later!
		// We're only a convenience function!
		Vector2 origin = mesh->getPreTransformVertices().getCentroid() * -1;
		mesh->getPreTransformVertices().move(origin.x * scale, origin.y * scale);

		result->addComponent(mesh);

		result->addComponent(new MeshDriverRenderer(
								 RenderMode::SHAPE | RenderMode::COLOR |
								 RenderMode::COLOR_TRANSORMED | (blend ? RenderMode::BLENDED : RenderMode::NONE)
								 ));
		return result;
	}


#endif
	
}
