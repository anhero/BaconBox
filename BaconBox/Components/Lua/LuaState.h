#ifndef BB_LUASTATE_H
#define BB_LUASTATE_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Core/Entity.h"

#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Input/Keyboard/Keyboard.h"

struct lua_State;
struct swig_type_info;


namespace BaconBox {
	class LuaState : public Component {
	public:
		BB_ID_HEADER;
		
		LuaState();
		~LuaState();
		void setLuaClass(lua_State * L);
		void reloadLuaClass();

		void update();
		void render();
					
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		
		
		void onPointerButtonPress(PointerButtonSignalData data);
		void onPointerButtonHold(PointerButtonSignalData data);
		void onPointerButtonRelease(PointerButtonSignalData data);
		void onPointerMove(PointerSignalData data);
		
		void onKeyPress(KeySignalData data);
		void onKeyRelease(KeySignalData data);
		void onKeyHold(KeySignalData data);

	private:
		static int EMPTY_LUA_REF;
	    
		
		int table_index;
		int update_index;
		int userData_index;
		
		int onPointerButtonPress_index;
		int onPointerButtonHold_index;
		int onPointerButtonRelease_index;
		int onPointerMove_index;
		
		int onKeyPress_index;
		int onKeyRelease_index;
		int onKeyHold_index;


		lua_State * L;
		
		
		swig_type_info* pointerButtonSignalData;
		swig_type_info* pointerSignalData;
		
		swig_type_info* keySignalData;



	};


	class LuaStateProxy : public ComponentProxy{
	public:
		
		
		LuaStateProxy(Entity* entity, bool mustAddComponent = true);
		void reloadLuaClass();
		void setLuaClass(lua_State * L);
	private:		

	};
}

#endif
