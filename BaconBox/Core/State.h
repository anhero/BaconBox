/**
 * @file
 */
#ifndef BB_STATE_H
#define BB_STATE_H

#include <string>
#include <vector>
#include <set>
#include <list>
#include "Entity.h"
#ifdef BB_LUA
#include "BaconBox/Components/Lua/LuaEntity.h"
#endif
#include "BaconBox/Components/HasName.h"

#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Components/UIManager.H"




#ifdef BB_LUA
struct lua_State;
#endif //BB_LUA

namespace BaconBox {
	class Camera;

	class State : public Entity,
		public HasNameProxy, public UIManagerProxy
#ifdef BB_LUA
, public LuaEntityProxy
#endif //BB_LUA
{
		friend class BaseEngine;
	public:
		BB_ID_HEADER;

		static const int MESSAGE_ADDED_ENTITY;
		static const int MESSAGE_REMOVED_ENTITY;
		static const int MESSAGE_GET_FOCUS;
		static const int MESSAGE_LOST_FOCUS;

		static const std::string DEFAULT_NAME;

		State(const std::string &newName = DEFAULT_NAME);

		virtual ~State();


		virtual void update();

		Entity * add(Entity *newEntity);
#ifdef BB_LUA
		Entity * add(lua_State * L);
#endif //BB_LUA
		void remove(Entity *newEntity);
#ifdef BB_LUA
		void remove(lua_State * L);
#endif //BB_LUA
		Camera &getCamera();

		const Camera &getCamera() const;

	protected:
		virtual void onGetFocus();

		virtual void onLoseFocus();
	private:
		void internalUpdate();

		void internalOnGetFocus();

		void internalOnLoseFocus();
	Camera *camera;
	};
}
#endif
