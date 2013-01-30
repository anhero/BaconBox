#ifndef BB_LUASTATE_H
#define BB_LUASTATE_H

#include "BaconBox/Core/Component.h"

struct lua_State;

namespace BaconBox {
	class LuaState : public Component {
	public:
		BB_ID_HEADER;
		
		LuaState();

		void setLuaClass(lua_State * L);
					
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
	private:

	};
}

#endif
