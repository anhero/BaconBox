#ifndef BB_LUAENTITY_H
#define BB_LUAENTITY_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Core/Entity.h"

#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Input/Keyboard/Keyboard.h"

#include "BaconBox/Components/AABBHitBox.h"

struct lua_State;
struct swig_type_info;


namespace BaconBox {
	class MovieClipEntity;
	class LuaEntity : public Component {
	public:
		BB_ID_HEADER;

		LuaEntity();
		~LuaEntity();
		void setLuaClass(lua_State * L);
		void reloadLuaClass();

		void update();

		virtual void receiveMessage(int senderID, int destID, int message, void *data);

		void addHitMask(MovieClipEntity* entity);

		void onPointerButtonPress(PointerButtonSignalData data);
		void onPointerButtonHold(PointerButtonSignalData data);
		void onPointerButtonRelease(PointerButtonSignalData data);
		void onPointerMove(PointerSignalData data);

		void onKeyPress(KeySignalData data);
		void onKeyRelease(KeySignalData data);
		void onKeyHold(KeySignalData data);

	private:

        void initializeConnections();


		static int EMPTY_LUA_REF;

        bool isClicked;

		int table_index;
		int update_index;
		int userData_index;

		int onPointerButtonPress_index;
		int onPointerButtonHold_index;
		int onPointerButtonRelease_index;
		int onPointerMove_index;

        int onPointerMoveOut_index;


		int onKeyPress_index;
		int onKeyRelease_index;
		int onKeyHold_index;


		lua_State * L;


		swig_type_info* pointerButtonSignalData;
		swig_type_info* pointerSignalData;

		swig_type_info* keySignalData;

        AABBHitBox * aabbHitBox;
		std::list<MovieClipEntity*> masks;

	};


	class LuaEntityProxy : public ComponentProxy{
	public:


		LuaEntityProxy(Entity* entity, bool mustAddComponent = true);
		void addHitMask(MovieClipEntity* entity);
		void reloadLuaClass();
		void setLuaClass(lua_State * L);
	private:

	};
}

#endif
