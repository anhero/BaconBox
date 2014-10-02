#include "BaconBox/Components/UIManager.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/Core/State.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/AABB.h"
#include "BaconBox/Display/Camera.h"


#ifdef BB_LUA
#include "BaconBox/Helper/Lua/LuaHelper.h"
#endif //BB_LUA


namespace BaconBox {
	BB_ID_IMPL(UIManager);

	UIManager::UIManager() : Component(), clickable(), camera(NULL), pointer(NULL), lastOver(NULL), currentlyPressed(NULL) {
		pointer = Pointer::getDefault();
	}
	
	UIManager::~UIManager(){
		for (std::list<MovieClipEntity*>::iterator i =  clickable.begin(); i != clickable.end(); i++) {
			(*i)->removeUIManagerReference();
		}
	}

	void UIManager::addClickable(MovieClipEntity *newEntity){
		newEntity->addToUIManager(this);
		clickable.push_front(newEntity);
	}
	
	void UIManager::removeClickable(MovieClipEntity *newEntity){
		newEntity->removeUIManagerReference();
		if (lastOver == newEntity) lastOver = NULL;
		clickable.remove(newEntity);
	}
#ifdef BB_LUA
	void UIManager::addClickable(lua_State * L){
		addClickable(reinterpret_cast<MovieClipEntity*>(LuaHelper::getEntityFromLuaEntity(L)));
	}
	
	void UIManager::removeClickable(lua_State * L){
		removeClickable(reinterpret_cast<MovieClipEntity*>(LuaHelper::getEntityFromLuaEntity(L)));
	}
#endif //BB_LUA


	void UIManager::update(){
		int cursor = 0;
        
        if(pointer->isButtonPressed(CursorButton::LEFT) || pointer->isButtonReleased(CursorButton::LEFT) || pointer->hasMoved(CursorButton::LEFT)){
		const Vector2 & pos = camera->getConcatMatrix().multiplyWithVector(pointer->getPosition());
		if(pointer->isButtonPressed(CursorButton::LEFT)){

			lastPressed = pointer->getPosition();
			for(std::list<MovieClipEntity*>::iterator i = clickable.begin(); i != clickable.end(); i++){
                PV(pos); PV((*i)->getAABB().getPosition()); PV((*i)->getAABB().getSize());
				if((*i)->getAABB().overlaps(pos)){
					(*i)->pressed->shoot();
					currentlyPressed = (*i);
					return;
				}
			}
		}
		else if(pointer->isButtonReleased(CursorButton::LEFT)){
			Vector2 diff(lastPressed - pointer->getPosition());
			if (diff.getLength() < 10){
			for(std::list<MovieClipEntity*>::iterator i = clickable.begin(); i != clickable.end(); i++){
				if((*i)->getAABB().overlaps(pos) && (*i)->isEnabled()){
					(*i)->released->shoot();
					currentlyPressed = NULL;
					return;
				}
				else if(lastOver){
					lastOver->moveOut->shoot();
				}
			}
			}
		}
		else if(pointer->hasMoved(CursorButton::LEFT)){
			if(lastOver && !lastOver->getAABB().overlaps(pos)){
				lastOver->moveOut->shoot();
				lastOver = NULL;
			}
			for(std::list<MovieClipEntity*>::iterator i = clickable.begin(); i != clickable.end(); i++){
				if((*i) == lastOver){
					return;
				}
				else if((*i)->getAABB().overlaps(pos)){
					if(lastOver)lastOver->moveOut->shoot();
					lastOver = *i;
					lastOver->moveOver->shoot();
					return;
				}
			}
		}
        }
	}



	
	
	void UIManager::receiveMessage(int senderID, int destID, int message, void *data) {
		Component::receiveMessage(senderID, destID, message, data);
        if (senderID == Entity::ID && message == Entity::MESSAGE_ADD_COMPONENT) {
            camera = &static_cast<State*>(this->getEntity())->getCamera();

        }
	}
	
	
	
	UIManagerProxy::UIManagerProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new UIManager())  {
	}
	
	
#ifdef BB_LUA
	void UIManagerProxy::addClickable(lua_State * L){
	    reinterpret_cast<UIManager*>(component)->addClickable(L);
	}
	void UIManagerProxy::removeClickable(lua_State * L){
	    reinterpret_cast<UIManager*>(component)->removeClickable(L);
	}
#endif //BB_LUA
	
	void UIManagerProxy::addClickable(MovieClipEntity *newEntity){
	    reinterpret_cast<UIManager*>(component)->addClickable(newEntity);
	}
	
	void UIManagerProxy::removeClickable(MovieClipEntity *newEntity){
	    reinterpret_cast<UIManager*>(component)->removeClickable(newEntity);
	}

}
