#include "LuaEntity.h"


#include "lua.hpp"
#include "BaconBox/Console.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Console.h"
#include "BaconBox/Core/IDManager.h"

swig_type_info * getTypeByName(lua_State* L, const char * name);
void pushLuaWrapperBySwigType(lua_State* L,void* ptr,swig_type_info *type,int own);
namespace BaconBox {
	 BB_ID_IMPL(LuaEntity);

	 int LuaEntity::EMPTY_LUA_REF = -1;

	LuaEntity::LuaEntity() : Component(), isClicked(false), aabbHitBox(NULL), table_index(EMPTY_LUA_REF), update_index(EMPTY_LUA_REF), userData_index(EMPTY_LUA_REF), onPointerButtonPress_index(EMPTY_LUA_REF),
		onPointerButtonHold_index(EMPTY_LUA_REF), onPointerButtonRelease_index(EMPTY_LUA_REF), onPointerMove_index(EMPTY_LUA_REF),
	onKeyPress_index(EMPTY_LUA_REF), onKeyRelease_index(EMPTY_LUA_REF), onKeyHold_index(EMPTY_LUA_REF), onPointerMoveOut_index(EMPTY_LUA_REF){
        initializeConnections();
	}
	LuaEntity::~LuaEntity(){
            disconnectAll();

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
			if(onPointerMoveOut_index != EMPTY_LUA_REF){
				luaL_unref(L, LUA_REGISTRYINDEX, onPointerMoveOut_index);
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


	void LuaEntity::initializeConnections(){
	    this->addConnection(new ComponentConnection<AABBHitBox>(&this->aabbHitBox));
    }

	void LuaEntity::update(){
	    if(update_index == EMPTY_LUA_REF)return;
		lua_rawgeti(L, LUA_REGISTRYINDEX,update_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 2, 0, 0);
		if(ret !=0){
			std::cout << "An error occured updating a LuaEntity. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}


	void LuaEntity::onKeyPress(KeySignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onKeyPress_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), keySignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onKeyPress in a LuaEntity. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}

	void LuaEntity::onKeyRelease(KeySignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onKeyRelease_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), keySignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onKeyRelease in a LuaEntity. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}
	void LuaEntity::onKeyHold(KeySignalData data){
		lua_rawgeti(L, LUA_REGISTRYINDEX,onKeyHold_index);
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), keySignalData, 0);
		lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
		int ret = lua_pcall(L, 3, 0, 0);
		if(ret !=0){
			std::cout << "An error occured calling onKeyHold in a LuaEntity. " <<std::endl;
			std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
		}
	}


	void LuaEntity::onPointerButtonPress(PointerButtonSignalData data){
        if(!aabbHitBox || aabbHitBox->getAABB().overlaps(data.getPosition())){
            lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerButtonPress_index);
            lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
            pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerButtonSignalData, 0);
            lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
            int ret = lua_pcall(L, 3, 0, 0);
            if(ret !=0){
                std::cout << "An error occured calling onPointerButtonPress in a LuaEntity. " <<std::endl;
                std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
            }
        }
	}

	void LuaEntity::onPointerButtonHold(PointerButtonSignalData data){
        if(!aabbHitBox || aabbHitBox->getAABB().overlaps(data.getPosition())){
            lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerButtonHold_index);
            lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
            pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerButtonSignalData, 0);
            lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
            int ret = lua_pcall(L, 3, 0, 0);
            if(ret !=0){
                std::cout << "An error occured calling onPointerButtonHold in a LuaEntity. " <<std::endl;
                std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
            }
        }
	}

	void LuaEntity::onPointerButtonRelease(PointerButtonSignalData data){
        if(!aabbHitBox || aabbHitBox->getAABB().overlaps(data.getPosition())){
            lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerButtonRelease_index);
            lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
            pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerButtonSignalData, 0);
            lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
            int ret = lua_pcall(L, 3, 0, 0);
            if(ret !=0){
                std::cout << "An error occured calling onPointerButtonRelease in a LuaEntity. " <<std::endl;
                std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
            }
        }
	}

	void LuaEntity::onPointerMove(PointerSignalData data){
        if((!aabbHitBox || aabbHitBox->getAABB().overlaps(data.getPosition())) && onPointerMove_index != EMPTY_LUA_REF){
            lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerMove_index);
            lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
            pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerSignalData, 0);
            lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
            int ret = lua_pcall(L, 3, 0, 0);
            if(ret !=0){
                std::cout << "An error occured calling onPointerMove in a LuaEntity. " <<std::endl;
                std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
            }
        }
        else if(aabbHitBox && onPointerMoveOut_index != EMPTY_LUA_REF){
            lua_rawgeti(L, LUA_REGISTRYINDEX,onPointerMoveOut_index);
            lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
            pushLuaWrapperBySwigType(L, reinterpret_cast<void*>(&data), pointerSignalData, 0);
            lua_rawgeti(L, LUA_REGISTRYINDEX,userData_index);
            int ret = lua_pcall(L, 3, 0, 0);
            if(ret !=0){
                std::cout << "An error occured calling onPointerMove in a LuaEntity. " <<std::endl;
                std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
            }
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




		//onPointerButtonPress
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onPointerButtonPress");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
				onPointerButtonPress_index = EMPTY_LUA_REF;
		}
		else{

		    onPointerButtonPress_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Pointer::connectButtonPress(this, &LuaEntity::onPointerButtonPress);
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
			Pointer::connectButtonHold(this, &LuaEntity::onPointerButtonHold);
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
			Pointer::connectButtonRelease(this, &LuaEntity::onPointerButtonRelease);
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
			Pointer::connectMove(this, &LuaEntity::onPointerMove);
		}

		//onPointerMoveOut
		lua_rawgeti(L, LUA_REGISTRYINDEX,table_index);
		lua_getfield(L, -1, "onPointerMoveOut");
		if(lua_isnil(L, -1)){
		    lua_pop(L, -1);
			onPointerMoveOut_index = EMPTY_LUA_REF;
		}
		else{
		    onPointerMoveOut_index = luaL_ref(L, LUA_REGISTRYINDEX);
			Pointer::connectMove(this, &LuaEntity::onPointerMove);
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
			Keyboard::connectKeyPress(this, &LuaEntity::onKeyPress);
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
			Keyboard::connectKeyRelease(this, &LuaEntity::onKeyRelease);
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
			Keyboard::connectKeyHold(this, &LuaEntity::onKeyHold);
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
	    if(getEntity() == Engine::getCurrentState()) this->reloadLuaClass();
	}

	void LuaEntity::receiveMessage(int senderID, int destID, int message, void *data) {
        Component::receiveMessage(senderID, destID, message, data);

	    if(senderID == State::ID){
		if(message == State::MESSAGE_LOSE_FOCUS){
		    disconnectAll();

		}
		else if(message == State::MESSAGE_GET_FOCUS){

		    reloadLuaClass();
		}

	    }
	}

	LuaEntityProxy::LuaEntityProxy(Entity * entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new LuaEntity()){
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
