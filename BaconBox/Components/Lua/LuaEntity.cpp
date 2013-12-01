#include "LuaEntity.h"


#include "lua.hpp"
#include "BaconBox/Console.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"
#include "BaconBox/Core/IDManager.h"


#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
swig_type_info * getTypeByName(lua_State* L, const char * name);
void pushLuaWrapperBySwigType(lua_State* L,void* ptr,swig_type_info *type,int own);
namespace BaconBox {
	 BB_ID_IMPL(LuaEntity);

	 int LuaEntity::EMPTY_LUA_REF = -1;

	LuaEntity::LuaEntity() : Component(), isClicked(false), aabbHitBox(NULL), table_index(EMPTY_LUA_REF), update_index(EMPTY_LUA_REF), userData_index(EMPTY_LUA_REF), onGetFocus_index(EMPTY_LUA_REF), onLostFocus_index(EMPTY_LUA_REF), receiveMessage_index(EMPTY_LUA_REF) {
        initializeConnections();
	}
	LuaEntity::~LuaEntity(){
            disconnectAll();
			removeSelfFromLuaRegistry();
	}
	
	void LuaEntity::removeSelfFromLuaRegistry(){
		if(L){
			if(table_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, table_index);
				table_index = EMPTY_LUA_REF;
			}
			if(update_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, update_index);
				update_index = EMPTY_LUA_REF;
			}
			
			if(userData_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, userData_index);
				userData_index = EMPTY_LUA_REF;
			}
			
			if(onGetFocus_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onGetFocus_index);
				onGetFocus_index = EMPTY_LUA_REF;
			}
			
			if(onLostFocus_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onLostFocus_index);
				onLostFocus_index = EMPTY_LUA_REF;
			}
			
			if(receiveMessage_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, receiveMessage_index);
				receiveMessage_index = EMPTY_LUA_REF;
			}
			
			//			if(onPointerButtonPress_index != EMPTY_LUA_REF){
			//				luaL_unref(L, LUA_REGISTRYINDEX, onPointerButtonPress_index);
			//			}
			//			if(onPointerButtonHold_index != EMPTY_LUA_REF){
			//				luaL_unref(L, LUA_REGISTRYINDEX, onPointerButtonHold_index);
			//			}
			//			if(onPointerButtonRelease_index != EMPTY_LUA_REF){
			//				luaL_unref(L, LUA_REGISTRYINDEX, onPointerButtonRelease_index);
			//			}
			//			if(onPointerMove_index != EMPTY_LUA_REF){
			//				luaL_unref(L, LUA_REGISTRYINDEX, onPointerMove_index);
			//			}
			//			if(onPointerMoveOut_index != EMPTY_LUA_REF){
			//				luaL_unref(L, LUA_REGISTRYINDEX, onPointerMoveOut_index);
			//			}
			//
			//
			//
			//			if(onKeyPress_index != EMPTY_LUA_REF){
			//				luaL_unref(L, LUA_REGISTRYINDEX, onKeyPress_index);
			//			}
			//			if(onKeyRelease_index != EMPTY_LUA_REF){
			//				luaL_unref(L, LUA_REGISTRYINDEX, onKeyRelease_index);
			//			}
			//			if(onKeyHold_index != EMPTY_LUA_REF){
			//				luaL_unref(L, LUA_REGISTRYINDEX, onKeyHold_index);
			//			}
		}
	}

	void LuaEntity::initializeConnections(){
	    this->addConnection(new ComponentConnection<AABBHitBox>(&this->aabbHitBox));
    }
	
	

	void LuaEntity::update(){
	    if(update_index == EMPTY_LUA_REF)return;
		lua_pushcfunction(L, LuaManager::errorHandler);
		lua_rawgeti(L, LUA_REGISTRYINDEX,update_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 2, 0, -4);
		if(ret !=0){
//			std::cout << "An error occured updating a LuaEntity. " <<std::endl;
//			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
//			exit(1);
		}
		lua_pop(L,1);

	}

	void LuaEntity::addHitMask(MovieClipEntity* entity){
		masks.push_back(entity);
	}

	
	
	void LuaEntity::onGetFocus(){
		lua_pushcfunction(L, LuaManager::errorHandler);
		lua_rawgeti(L, LUA_REGISTRYINDEX,onGetFocus_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 2, 0, -4);
		lua_pop(L,1);

		if(ret !=0){
//			std::cout << "An error occured calling onGetFocus in a LuaEntity. " <<std::endl;
//			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
//			exit(1);
		}
	}
	
	void LuaEntity::onLostFocus(){
		lua_pushcfunction(L, LuaManager::errorHandler);
		lua_rawgeti(L, LUA_REGISTRYINDEX,onLostFocus_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 2, 0, -4);
		lua_pop(L,1);

		if(ret !=0){
//			std::cout << "An error occured calling onLostFocus in a LuaEntity. " <<std::endl;
//			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;

		}
	}


	void LuaEntity::reloadLuaClass(){
		disconnectAll();

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
		
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onGetFocus");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			
			onGetFocus_index = EMPTY_LUA_REF;
		}
		else{
		   onGetFocus_index = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onLostFocus");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			
			onLostFocus_index = EMPTY_LUA_REF;
		}
		else{
		    onLostFocus_index = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "receiveMessage");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			
			receiveMessage_index = EMPTY_LUA_REF;
		}
		else{
		   receiveMessage_index = luaL_ref(L, LUA_REGISTRYINDEX);
		}

	}

	void LuaEntity::setLuaClass(lua_State * L){
	    if(!lua_istable(L,-1)){
		Console::error("Lua Parameter of LuaEntity::setLuaClass must be a table");
		return;
	    }
	    if(!lua_isuserdata(L,-2)){
		Console::error("LuaEntity::setLuaClass must be called on a LuaEntity or LuaEntityProxy object.");
		return;
	    }
	    table_index = luaL_ref(L, LUA_REGISTRYINDEX);
	    userData_index = luaL_ref(L, LUA_REGISTRYINDEX);
	    this->L = L;


		//Swig types
		pointerButtonSignalData = getTypeByName(L, "PointerButtonSignalData");
		pointerSignalData = getTypeByName(L, "PointerSignalData");
		keySignalData = getTypeByName(L, "KeySignalData");
	    this->reloadLuaClass();
	}

	void LuaEntity::receiveMessage(int senderID, int destID, int message, void *data) {
        Component::receiveMessage(senderID, destID, message, data);

	    if(senderID == State::ID){
		if(message == State::MESSAGE_LOST_FOCUS && onLostFocus_index != EMPTY_LUA_REF){
			onLostFocus();
//		    disconnectAll();

		}
		else if(message == State::MESSAGE_GET_FOCUS && onGetFocus_index != EMPTY_LUA_REF){
			onGetFocus();
//		    reloadLuaClass();
		}

	    }
		if(receiveMessage_index != EMPTY_LUA_REF){
			//call lua receiveMessage
		}

	}

	LuaEntityProxy::LuaEntityProxy(Entity * entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new LuaEntity()){
	}
	void LuaEntityProxy::removeSelfFromLuaRegistry(){
	    reinterpret_cast<LuaEntity*>(component)->removeSelfFromLuaRegistry();
	}
	
	void LuaEntityProxy::addHitMask(MovieClipEntity* entity){
	    reinterpret_cast<LuaEntity*>(component)->addHitMask(entity);
	}

	void LuaEntityProxy::reloadLuaClass(){
	    reinterpret_cast<LuaEntity*>(component)->reloadLuaClass();
	}

	void LuaEntityProxy::setLuaClass(lua_State * L){
		if(component){
			reinterpret_cast<LuaEntity*>(component)->setLuaClass(L);
		}
		else{
			component = entity->getComponent(LuaEntity::ID);
			if(!component) Console::error("Call to setLuaClass on an entity with no LuaEntity Component!");
			reinterpret_cast<LuaEntity*>(component)->setLuaClass(L);
		}
	}


}
