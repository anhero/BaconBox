#include "LuaState.h"


#include "BaconBox/Core/State.h"
#include "lua.hpp"
#include "BaconBox/Console.h"
#include "BaconBox/Core/Engine.h"

swig_type_info * getTypeByName(lua_State* L, const char * name);
void pushLuaWrapperBySwigType(lua_State* L,void* ptr,swig_type_info *type,int own);
namespace BaconBox {
	 BB_ID_IMPL(LuaState);
	
	 int LuaState::EMPTY_LUA_REF = -1;
	 
	LuaState::LuaState() : Component(), table_index(EMPTY_LUA_REF), update_index(EMPTY_LUA_REF), userData_index(EMPTY_LUA_REF), onPointerButtonPress_index(EMPTY_LUA_REF), 
		onPointerButtonHold_index(EMPTY_LUA_REF), onPointerButtonRelease_index(EMPTY_LUA_REF), onPointerMove_index(EMPTY_LUA_REF),
	onKeyPress_index(EMPTY_LUA_REF), onKeyRelease_index(EMPTY_LUA_REF), onKeyHold_index(EMPTY_LUA_REF){
		
	}
	LuaState::~LuaState(){
		if(L){
			if(table_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, table_index);
			}
			if(update_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, update_index);
			}
			if(userData_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, userData_index);
			}
			
			if(onPointerButtonPress_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onPointerButtonPress_index);
			}
			if(onPointerButtonHold_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onPointerButtonHold_index);
			}
			if(onPointerButtonRelease_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onPointerButtonRelease_index);
			}
			if(onPointerMove_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onPointerMove_index);
			}
			
			
			if(onKeyPress_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onKeyPress_index);
			}
			if(onKeyRelease_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onKeyRelease_index);
			}
			if(onKeyHold_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onKeyHold_index);
			}
		}
	}

	void LuaState::update(){
	    if(update_index == EMPTY_LUA_REF)return;
		lua_rawgeti(L, LUA_REGISTRYINDEX,update_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 2, 0, 0);
		if(ret !=0){
			std::cout << "An error occured updating a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}

	void LuaState::render(){

	}
	void LuaState::onKeyPress(KeySignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onKeyPress_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), keySignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onKeyPress in a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	
	void LuaState::onKeyRelease(KeySignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onKeyRelease_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), keySignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onKeyRelease in a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	void LuaState::onKeyHold(KeySignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onKeyHold_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), keySignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onKeyHold in a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	
	
	void LuaState::onPointerButtonPress(PointerButtonSignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerButtonPress_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerButtonSignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onPointerButtonPress in a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	
	void LuaState::onPointerButtonHold(PointerButtonSignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerButtonHold_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerButtonSignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onPointerButtonHold in a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	
	void LuaState::onPointerButtonRelease(PointerButtonSignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerButtonRelease_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerButtonSignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onPointerButtonRelease in a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	
	void LuaState::onPointerMove(PointerSignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerMove_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerSignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onPointerMove in a LuaState. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	
	void LuaState::reloadLuaClass(){
		Pointer::getDefault()->buttonPress.disconnect(this);
		Pointer::getDefault()->buttonHold.disconnect(this);
		Pointer::getDefault()->buttonRelease.disconnect(this);
		Pointer::getDefault()->move.disconnect(this);

		Keyboard::getDefault()->keyPress.disconnect(this);
		Keyboard::getDefault()->keyRelease.disconnect(this);
		Keyboard::getDefault()->keyHold.disconnect(this);
		    
	    if(table_index == EMPTY_LUA_REF || userData_index == EMPTY_LUA_REF) return;
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "update");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);

				update_index = EMPTY_LUA_REF;
		}
		else{
		    update_index = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		
		
		//onPointerButtonPress
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onPointerButtonPress");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
				onPointerButtonPress_index = EMPTY_LUA_REF;
		}
		else{
			
		    onPointerButtonPress_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Pointer::connectButtonPress(this, &LuaState::onPointerButtonPress);
		}
		
		//onPointerButtonHold
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onPointerButtonHold");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			onPointerButtonHold_index = EMPTY_LUA_REF;
		}
		else{
		    onPointerButtonHold_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Pointer::connectButtonHold(this, &LuaState::onPointerButtonHold);
		}
		
		//onPointerButtonRelease
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onPointerButtonRelease");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			onPointerButtonRelease_index = EMPTY_LUA_REF;
		}
		else{
		    onPointerButtonRelease_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Pointer::connectButtonRelease(this, &LuaState::onPointerButtonRelease);
		}
		
		//onPointerMove
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onPointerMove");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			onPointerMove_index = EMPTY_LUA_REF;
		}
		else{
		    onPointerMove_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Pointer::connectMove(this, &LuaState::onPointerMove);
		}
		
		//onKeyPress
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onKeyPress");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			onKeyPress_index = EMPTY_LUA_REF;
		}
		else{
		    onKeyPress_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Keyboard::connectKeyPress(this, &LuaState::onKeyPress);
		}
		
		
		//onKeyRelease
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onKeyRelease");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			onKeyRelease_index = EMPTY_LUA_REF;
		}
		else{
		    onKeyRelease_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Keyboard::connectKeyRelease(this, &LuaState::onKeyRelease);
		}
		
		
		//onKeyHold
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onKeyHold");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			onKeyHold_index = EMPTY_LUA_REF;
		}
		else{
		    onKeyHold_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Keyboard::connectKeyHold(this, &LuaState::onKeyHold);
		}
	}

	void LuaState::setLuaClass(lua_State * L){
	    if(!lua_istable(L,-1)){
		Console::error("Lua Parameter of LuaState::setLuaClass must be a table");
		return;
	    }
	    if(!lua_isuserdata(L,-2)){
		Console::error("LuaState::setLuaClass must be called on a LuaState or LuaStateProxy object."); 
		return;
	    }
	    table_index = luaL_ref(L, LUA_REGISTRYINDEX);
	    userData_index = luaL_ref(L, LUA_REGISTRYINDEX);
	    this->L = L;
		
		
		//Swig types
		pointerButtonSignalData = getTypeByName(L, "PointerButtonSignalData");
		pointerSignalData = getTypeByName(L, "PointerSignalData");
		keySignalData = getTypeByName(L, "KeySignalData");
	    if(getEntity() == Engine::getCurrentState()) this->reloadLuaClass();
	}

	void LuaState::receiveMessage(int senderID, int destID, int message, void *data) {

	    if(senderID == State::ID){
		if(message == State::MESSAGE_LOSE_FOCUS){
		    Pointer::getDefault()->buttonPress.disconnect(this);
		    Pointer::getDefault()->buttonHold.disconnect(this);
		    Pointer::getDefault()->buttonRelease.disconnect(this);
		    Pointer::getDefault()->move.disconnect(this);
		    
		    Keyboard::getDefault()->keyPress.disconnect(this);
		    Keyboard::getDefault()->keyRelease.disconnect(this);
		    Keyboard::getDefault()->keyHold.disconnect(this);

		}
		else if(message == State::MESSAGE_GET_FOCUS){
		    
		    reloadLuaClass();
		}

	    }
	}
	
	LuaStateProxy::LuaStateProxy(Entity * entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new LuaState()){
	}

	void LuaStateProxy::reloadLuaClass(){
	    reinterpret_cast<LuaState*>(component)->reloadLuaClass();
	}
	
	void LuaStateProxy::setLuaClass(lua_State * L){
		if(component){
			reinterpret_cast<LuaState*>(component)->setLuaClass(L);
		}
		else{
			component = entity->getComponent(LuaState::ID);
			if(!component) Console::error("Call to setLuaClass on an entity with no LuaStateComponent!");
			reinterpret_cast<LuaState*>(component)->setLuaClass(L);
		}
	}


}