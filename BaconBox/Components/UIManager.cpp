#include "BaconBox/Components/UIManager.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/Core/State.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/AxisAlignedBoundingBox.h"


#ifdef BB_LUA
#include "BaconBox/Helper/Lua/LuaHelper.h"
#endif //BB_LUA


namespace BaconBox {
	BB_ID_IMPL(UIManager);

	UIManager::UIManager() : Component(), clickable(), lastOver(NULL), currentlyPressed(NULL) {
		
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


	void UIManager::disconnect(){
		Pointer::getDefault()->buttonRelease.disconnect(this);
		Pointer::getDefault()->buttonPress.disconnect(this);
		Pointer::getDefault()->move.disconnect(this);
	}
	
	void UIManager::connect(){
		Pointer::getDefault()->buttonRelease.connect(this, &UIManager::pointerButtonRelease);
		Pointer::getDefault()->buttonPress.connect(this, &UIManager::pointerButtonPress);
		Pointer::getDefault()->move.connect(this, &UIManager::pointerMove);
	}
	
	
	void UIManager::pointerButtonRelease(PointerButtonSignalData data){
		for(std::list<MovieClipEntity*>::iterator i = clickable.begin(); i != clickable.end(); i++){
			if((*i)->getAABB().overlaps(data.getPosition())){
				(*i)->released->shoot();
				currentlyPressed = NULL;
				return;
			}
			else if(lastOver){
				lastOver->moveOut->shoot();
			}
		}
	}
	
	void UIManager::pointerButtonPress(PointerButtonSignalData data){
		for(std::list<MovieClipEntity*>::iterator i = clickable.begin(); i != clickable.end(); i++){
			if((*i)->getAABB().overlaps(data.getPosition())){
				(*i)->pressed->shoot();
				currentlyPressed = (*i);
				return;
			}
		}
	}
	
	void UIManager::pointerMove(PointerSignalData data){
		if(lastOver && !lastOver->getAABB().overlaps(data.getPosition())){
			lastOver->moveOut->shoot();
			lastOver = NULL;
		}
		for(std::list<MovieClipEntity*>::iterator i = clickable.begin(); i != clickable.end(); i++){
			if((*i) == lastOver){
				return;
			}
			else if((*i)->getAABB().overlaps(data.getPosition())){
				if(lastOver)lastOver->moveOut->shoot();
				lastOver = *i;
				lastOver->moveOver->shoot();
				return;
			}
		}
	}
	
	
	
	void UIManager::receiveMessage(int senderID, int destID, int message, void *data) {
		Component::receiveMessage(senderID, destID, message, data);
		
		if(senderID != State::ID) return;
		if(message == State::MESSAGE_LOST_FOCUS){
			disconnect();
		}
		else if(message == State::MESSAGE_GET_FOCUS){
			connect();
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
