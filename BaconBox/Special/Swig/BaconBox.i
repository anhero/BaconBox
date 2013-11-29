
%module BaconBox

#if defined(BB_LUA)
	%native(cast) int luacast(lua_State*L);
  %native(own) int luaOwn(lua_State*L);

%luacode {
  function class(base, init)
   local c = {}    -- a new class instance
   if not init and type(base) == 'function' then
      init = base
      base = nil
   elseif type(base) == 'table' then
    -- our new class is a shallow copy of the base class!
      for i,v in pairs(base) do
         c[i] = v
      end
      c._base = base
   end
   -- the class will be the metatable for all its objects,
   -- and they will look up their methods in it.
   c.__index = c

   -- expose a constructor which can be called by <classname>(<args>)
   local mt = {}
   mt.__call = function(class_tbl, ...)
   local obj = {}
   setmetatable(obj,c)
   if class_tbl.init then
      class_tbl.init(obj,...)
   else 
      -- make sure that any stuff from the base class is initialized!
      if base and base.init then
      base.init(obj, ...)
      end
   end
   return obj
   end
   c.init = init
   c.is_a = function(self, klass)
      local m = getmetatable(self)
      while m do 
         if m == klass then return true end
         m = m._base
      end
      return false
   end
   setmetatable(c, mt)
   return c
end

LuaEntity = class()
function LuaEntity:init(entity)
  self.entity = entity
  self.entity:setLuaClass(self)
  for key, value in pairs(getmetatable(self.entity)[".fn"]) do
      if self[key] == nil  and key ~=  "update" then
        self[key] = function(self, ...) return self.entity[key](self.entity, ...);end
      end
  end
end



LuaState = class(LuaEntity)
function LuaState:init(name)
  LuaEntity.init(self, BaconBox.State(name))
  self.state = self.entity
end

function printTable(table)
  for k,v in pairs(table) do
    print(k,v)
  end
end


function printUserData(userdata)
  local meta = getmetatable(userdata)
  print("Printing function of", userdata)
  print("--- Function ---")
  printTable(meta[".fn"])

  print("--- Set ---")
  printTable(meta[".set"])

  print("--- Get ---")
  printTable(meta[".get"]) 

end

}
#endif


%{


  #ifdef BB_LUA
    #include "BaconBox/Script/Lua/LuaCallback.h"
    #include "BaconBox/Helper/Lua/LuaHelper.h"
  #endif

    #include "BaconBox/Helper/URL.h"

  #include "BaconBox/Helper/SafeEnum.h"
  #include "BaconBox/Platform.h"

	#include "BaconBox/PlatformFlagger.h"
	#include "BaconBox/Core/IDManager.h"
  #ifdef BB_FLASH_PLATFORM
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
	#include "BaconBox/Components/Flash/MovieClipHolder.h" 
	#endif //BB_FLASH_PLATFORM


  #include "BaconBox/Display/Window/WindowOrientation.h"
  #include "BaconBox/Display/Window/MainWindow.h"

  #include "BaconBox/Input/InputState.h"
  #include "BaconBox/Input/InputSignalData.h"
  #include "BaconBox/Input/Pointer/CursorButton.h"


  #include "BaconBox/SignalSlots/SignalData.h"

  #include "BaconBox/Input/Keyboard/Key.h"
  #include "BaconBox/Input/Keyboard/Keyboard.h"
  #include "BaconBox/Input/Keyboard/KeyboardState.h"

  #include "BaconBox/Input/Keyboard/KeySignalData.h"
  #include "BaconBox/Input/Keyboard/KeyMaskSignalData.h"

  #include "BaconBox/Input/Pointer/CursorState.h"
  #include "BaconBox/Input/Pointer/PointerState.h"
  #include "BaconBox/Input/Pointer/PointerSignalData.h"
  #include "BaconBox/Input/Pointer/PointerButtonSignalData.h"
  #include "BaconBox/Input/Pointer/Pointer.h"


#include "BaconBox/Input/Accelerometer/AccelerometerState.h"
#include "BaconBox/Input/Accelerometer/AccelerometerSignalData.h"
#include "BaconBox/Input/Accelerometer/Accelerometer.h"

#include "BaconBox/Input/GamePad/GamePadState.h"
#include "BaconBox/Input/GamePad/GamePadSignalData.h"
#include "BaconBox/Input/GamePad/GamePadThumbstickSignalData.h"
#include "BaconBox/Input/GamePad/GamePadButtonSignalData.h"
#include "BaconBox/Input/GamePad/GamePad.h"

  #include "BaconBox/Input/InputManager.h"


	#include "BaconBox/Core/Component.h"
	#include "BaconBox/Core/Entity.h"
  #include "BaconBox/Display/Color.h"
  #include "BaconBox/ColorMatrix.h" 
  #include "BaconBox/Components/ColorTransform.h"
  #include "BaconBox/Components/HasName.h"

	#include "BaconBox/Vector2.h"
    #include "BaconBox/Vector3.h"

  #include "BaconBox/Components/Visibility.h"
	#include "BaconBox/Components/Transform.h"
  #include "BaconBox/Display/ColorFormat.h"
  #include "BaconBox/Display/TextureInformation.h"


  #include "BaconBox/Display/SubTextureInfo.h"
#include "BaconBox/Helper/Stopwatch.h"

#include "BaconBox/Helper/Ease.h"

#include "BaconBox/Helper/MathHelper.h"

#include "BaconBox/Helper/TimeHelper.h"
#include "BaconBox/Components/Speed.h"
#include "BaconBox/Components/Shake.h"

#include "BaconBox/Display/ParticlePhase.h"
#include "BaconBox/Display/Particle.h"
#include "BaconBox/Display/Emitter.h"
#include "BaconBox/Components/ParticleEmitter.h"
	
	#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
	 #include "BaconBox/Line.h"


#include "BaconBox/EmitterEntity.h"
	
	#include "BaconBox/EntityFactory.h"
#include "BaconBox/Helper/EmitterFactory.h"
  #include "BaconBox/Components/HasName.h"
  #include "BaconBox/Components/CameraPositionConverter.h"

  #include "BaconBox/Display/Camera.h"
  #include "BaconBox/Core/State.h"
  #include "BaconBox/Core/Engine.h"
  #include "BaconBox/Display/Text/FontFormat.h"
    #include "BaconBox/Components/Timeline.h"

  #include "BaconBox/Components/LineComponent.h"
  #include "BaconBox/Components/EntityContainer.h"

  #include "BaconBox/Display/Text/Font.h"
  #include "BaconBox/Helper/ResourcePathHandler.h"
  #include "BaconBox/Display/PixMap.h"

  #include "BaconBox/Audio/SoundParameters.h"
  #include "BaconBox/Audio/MusicParameters.h"

  #include "BaconBox/ResourceManager.h"
#include "BaconBox/Display/Text/TextAlignment.h"
#include "BaconBox/Components/TextComponent.h"
#include "BaconBox/Display/Text/TextEntity.h"
#include "BaconBox/AxisAlignedBoundingBox.h"
  #include "BaconBox/Components/AABBHitBox.h"

  #include "BaconBox/Components/SizeComponent.h"
#include "BaconBox/LocalizationManager.h"


#include "BaconBox/Symbol.h"


#include <sstream>

#if defined(BB_LUA)
  #include "BaconBox/Components/Lua/LuaEntity.h"
#endif

namespace BaconBox{
class BaseEngine;
#ifdef BB_FLASH_PLATFORM
class FlashEngine;
#endif
}

///////////////////////
// Helper functions
///////////////////////
#if defined(BB_LUA)
	swig_type_info * getTypeByName(swig_module_info *start,
        swig_module_info *end,
  const char *name){
  swig_module_info *iter = start;
  do {
  register size_t i = 0;
  for (; i < iter->size; ++i) {
    swig_lua_class* luaclass = (swig_lua_class*) iter->types[i]->clientdata;
    if(luaclass&& strcmp(luaclass->name, name) ==0){
      return iter->types[i];
    }
  }
  iter = iter->next;
} while (iter != end);
  return NULL;
}

swig_type_info * getTypeByName(lua_State*L, const char * name){
  swig_module_info *module =SWIG_GetModule(L);
  return getTypeByName(module, module, name);
}

 int luaOwn(lua_State*L){
    swig_lua_userdata* usr;
    usr=(swig_lua_userdata*)lua_touserdata(L,-1);
    usr->own = 1;
    return 0;
  }

  int luacast(lua_State*L){
    void * myDataPtr;
        void ** ptrToPtr = &myDataPtr;

        const char * type_name = luaL_checkstring(L, 2);
    swig_type_info * type = getTypeByName(L, type_name);

        SWIG_ConvertPtr(L, 1, ptrToPtr, NULL, 0);


        // Search the SWIG module for a swig_type_info that contains the data
        // type string that was passed as the second parameter

        if(type == NULL)
        {

                lua_pushnumber(L, -2);
                lua_pushstring(L,"Failed to find swig_type_info for specified type.");
                return 2;
        }
    
        // Using the swig_type_info that we found, create a new object on 
        // the stack of the desired data type and return.
        SWIG_Lua_NewPointerObj(L, myDataPtr, type, 0);

        return 1;
  }

  
	#endif

class SoundInfo;
#include "BaconBox/Audio/AudioState.h"
#include "BaconBox/Audio/AudioEngine.h"
#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/Sound.h"

#include "BaconBox/Audio/SoundFX.h"

#include "BaconBox/Audio/MusicEngine.h"
#include "BaconBox/Audio/BackgroundMusic.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"
#include "BaconBox/vmath.h"

%}

%ignore Color::operator uint32_t() const;


namespace BaconBox{
class BaseEngine;

#ifdef BB_FLASH_PLATFORM
class FlashEngine;
#endif

}

%include "BaconBox/Core/IDManager.h"

%ignore onPointerMove(PointerButtonSignalData);




#if defined(BB_LUA)
		%include "std_string.i"


%typemap(arginit) SWIGTYPE *self %{
  swig_type_info * selfType = $descriptor;
    SWIG_ConvertPtr(L,1,(void**)&$1,selfType,0);
%}



   %typecheck(SWIG_TYPECHECK_POINTER)lua_State* {
      $1 = lua_istable(L,$input);
    }

  %typemap(arginit) lua_State* %{
    #ifdef IMPOSSIBLE_MACRO_JUST_TO_SKIP_SWIG_ARG_COUNT_CHECK_I_SHOULD_REALLY_FIND_A_FIX_IN_THE_NEAR_FUTURE
    %}
    
 

    %typemap(in) (lua_State*) %{ 
   #endif //IMPOSSIBLE_MACRO_JUST_TO_SKIP_SWIG_ARG_COUNT_CHECK_I_SHOULD_REALLY_FIND_A_FIX_IN_THE_NEAR_FUTURE
        
    $1 = L;
    %}



#endif


#pragma SWIG nowarn=325



#ifdef BB_AS3_SWIG


%typemap(astype) (AS3::local::var) "*";

%typemap(in) (AS3::local::var aMC) {
	AS3_GetVarxxFromVar($1, $input);
}



%rename("getComponentByID") getComponent(int) const;
%rename("getComponentByName") getComponent(const std::string &) const;


%ignore Component(const Component &src);
%ignore Entity(const Entity &src);
%ignore Transform(const Transform &src);


#endif





%include "sigly.h"



%template(HasSlots_SingleThreaded) sigly::HasSlots< sigly::SingleThreaded >;
%template(signal_base) sigly::_signal_base< sigly::SingleThreaded >;

%template(signal_base0)sigly::_signal_base0< sigly::SingleThreaded >;
%template(signal) sigly::Signal0< sigly::SingleThreaded >;

%template(signal_base1_KeySignalData)sigly::_signal_base1< BaconBox::KeySignalData,sigly::SingleThreaded >;
%template(signal_KeySignalData) sigly::Signal1< BaconBox::KeySignalData,sigly::SingleThreaded >;

%template(signal_base1_KeyMaskSignalData)sigly::_signal_base1< BaconBox::KeyMaskSignalData,sigly::SingleThreaded >;
%template(signal_KeyMaskSignalData) sigly::Signal1< BaconBox::KeyMaskSignalData,sigly::SingleThreaded >;

%template(signal_base1_AccelerometerSignalData)sigly::_signal_base1< BaconBox::AccelerometerSignalData,sigly::SingleThreaded >;
%template(signal_AccelerometerSignalData) sigly::Signal1< BaconBox::AccelerometerSignalData,sigly::SingleThreaded >;

%template(signal_base1_PointerSignalData)sigly::_signal_base1< BaconBox::PointerSignalData,sigly::SingleThreaded >;
%template(signal_PointerSignalData) sigly::Signal1< BaconBox::PointerSignalData,sigly::SingleThreaded >;

%template(signal_base1_PointerButtonSignalData)sigly::_signal_base1< BaconBox::PointerButtonSignalData,sigly::SingleThreaded >;
%template(signal_PointerButtonSignalData) sigly::Signal1< BaconBox::PointerButtonSignalData,sigly::SingleThreaded >;


%template(signal_base1_void)sigly::_signal_base1< void*,sigly::SingleThreaded >;
%template(signal_void) sigly::Signal1< void*,sigly::SingleThreaded >;

%extend  sigly::_signal_base<sigly::SingleThreaded> {
  void connect(lua_State*L, const std::string & type = ""){
    int paramCount = 0;
    while(lua_isstring(L, -1)) {
      paramCount++;
      lua_pop (L, 1);
    }
    BaconBox::LuaCallback * cb = new BaconBox::LuaCallback(L, type);

    switch(paramCount){
      case 0:
        BaconBox::LuaHelper::connectSignal0(L, cb);
        break;
      case 1:
        BaconBox::LuaHelper::connectSignal1(L, cb);
        break;
    }
  }

   void disconnectCB(lua_State*L){
      if(lua_isuserdata(L,-2) && lua_istable(L,-1) ){
        lua_getfield(L, -1, "disconnect");
        lua_pushvalue(L, -2);
        lua_pushvalue(L, -4);
        sigly::Signal1<void*> * signal = reinterpret_cast<sigly::Signal1<void*> *>(BaconBox::LuaHelper::getPointerFromLuaUserData(L, false));
        lua_pushlightuserdata(L, signal);

        int ret = lua_pcall(L, 3, 0, 0);
        if(ret !=0){
          std::cout << "An error occured calling disconnect() on a lua Callback in disconnectCB. " <<std::endl;
          std::cout << "Error : " << lua_tostring(L, -1) << std::endl;
        }
        lua_pop (L, 2);
      }
      else{
        Console__error("disconnectCB wasn't able to disconnect signal, wrong parameter were given.");
      }
  }
};

namespace BaconBox{
class MovieClipEntity;
}

#ifdef BB_LUA
  %include "BaconBox/Script/Lua/LuaCallback.h"
#endif

%include "BaconBox/Helper/SafeEnum.h"



%include "BaconBox/Core/Component.h"

%include "BaconBox/Components/UIManager.h"
%include "BaconBox/Components/Clickable.h"


%include "BaconBox/Components/HasName.h"

%include "BaconBox/Core/Entity.h"
%include "BaconBox/Display/Color.h"
%include "BaconBox/ColorMatrix.h" 
%include "BaconBox/Components/ColorTransform.h" 

//%include "BaconBox/Vector2.h"

%include "BaconBox/vmath.h"

%template(Vector3f) VMATH_NAMESPACE::Vector3< float >;
%template(Matrix4f) VMATH_NAMESPACE::Matrix4< float >;
%template(Quatf) VMATH_NAMESPACE::Quaternion< float >;

%extend VMATH_NAMESPACE::Vector3<float> {
const char *__str__() {
       static char tmp[1024];
       std::stringstream ss;
        ss << (*self);
        strcpy(tmp, ss.str().c_str());
        return tmp;
   }

}

namespace BaconBox{
	class Vector2{
		public:
		Vector2();
		#if defined(BB_LUA)
		Vector2(float x, float y);
		#endif

    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator+(float delta) const;

    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator-(float delta) const;


    float operator*(const Vector2 &other) const;
    Vector2 operator*(float delta) const;

    Vector2 operator/(float delta) const;


  
    float getLength() const;
    void setLength(float newLength);
    float getSquaredLength() const;
    float getDotProduct(const Vector2 &other) const;
    Vector2 getNormalized() const;
    void normalize();
    Vector2 &coordinatesMultiply(const Vector2 &other);
    Vector2 getCoordinatesMultiplication(const Vector2 &other) const;
    Vector2 &coordinatesDivide(const Vector2 &other);
    Vector2 getCoordinatesDivision(const Vector2 &other) const;
    float getAngle() const;
    float getAngleBetween(const Vector2 &other) const;
    void setAngle(float newAngle);
    Vector2 getRotated(float angle) const;
    void rotate(float angle);
    Vector2 getProjection(const Vector2 &direction) const;
    void project(const Vector2 &direction);
    Vector2 getReflected(const Vector2 &mirror) const;
    void reflect(const Vector2 &mirror);


		float x;
		float y;

	};

    class Vector3{
    public:
    Vector3();
    Vector3(const Vector3 &);

    #if defined(BB_LUA)
    Vector3(float x, float y, float z);
    #endif

    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator+(float delta) const;

    Vector3 operator-(const Vector3 &other) const;
    Vector3 operator-(float delta) const;


    float operator*(const Vector3 &other) const;
    Vector3 operator*(float delta) const;

    Vector3 operator/(float delta) const;


  
    float getLength() const;
    void setLength(float newLength);
    float getSquaredLength() const;
    float getDotProduct(const Vector3 &other) const;
    Vector3 getNormalized() const;
    void normalize();

    float x;
    float y;
    float z;
  };

}

%extend BaconBox::Vector2 {
const char *__str__() {
       static char tmp[1024];
       std::stringstream ss;
        ss << (*self);
        strcpy(tmp, ss.str().c_str());
        return tmp;
   }

}

%extend BaconBox::Vector3 {
const char *__str__() {
       static char tmp[1024];
       std::stringstream ss;
        ss << (*self);
        strcpy(tmp, ss.str().c_str());
        return tmp;
   }

}

%include "BaconBox/Matrix2D.h"
%include "BaconBox/Helper/URL.h"

%include "BaconBox/PlatformFlagger.h"
%include "BaconBox/Platform.h"

%include "BaconBox/Input/InputState.h"
%include "BaconBox/SignalSlots/SignalData.h"

%include "BaconBox/Display/Window/WindowOrientation.h"
%include "BaconBox/Display/Window/MainWindow.h"

%include "BaconBox/Input/InputSignalData.h"

%include "BaconBox/Input/InputDevice.h"

%include "BaconBox/Input/Keyboard/Key.h"
%include "BaconBox/Input/Keyboard/KeyboardState.h"
%include "BaconBox/Input/Keyboard/KeyboardSignalData.h"
%include "BaconBox/Input/Keyboard/KeySignalData.h"
%include "BaconBox/Input/Keyboard/KeyMaskSignalData.h"




%immutable BaconBox::Keyboard::keyPress;
%immutable BaconBox::Keyboard::keyHold;
%immutable BaconBox::Keyboard::keyRelease;
%immutable BaconBox::Keyboard::keyMaskPress;
%immutable BaconBox::Keyboard::keyMaskHold;
%immutable BaconBox::Keyboard::keyMaskRelease;
%include "BaconBox/Input/Keyboard/Keyboard.h"

%include "BaconBox/Input/Pointer/CursorButton.h"

%include "BaconBox/Input/Pointer/CursorState.h"
%include "BaconBox/Input/Pointer/PointerState.h"
%include "BaconBox/Input/Pointer/PointerSignalData.h"
%include "BaconBox/Input/Pointer/PointerButtonSignalData.h"

%immutable BaconBox::Pointer::buttonPress;
%immutable BaconBox::Pointer::buttonHold;
%immutable BaconBox::Pointer::buttonRelease;
%immutable BaconBox::Pointer::move;
%include "BaconBox/Input/Pointer/Pointer.h"


%include "BaconBox/Input/Accelerometer/AccelerometerState.h"

%include "BaconBox/Input/Accelerometer/AccelerometerSignalData.h"

%immutable BaconBox::Accelerometer::change;
%include "BaconBox/Input/Accelerometer/Accelerometer.h"

%include "BaconBox/Input/GamePad/GamePadState.h"
%include "BaconBox/Input/GamePad/GamePadSignalData.h"
%include "BaconBox/Input/GamePad/GamePadThumbstickSignalData.h"
%include "BaconBox/Input/GamePad/GamePadButtonSignalData.h"
%include "BaconBox/Input/GamePad/GamePad.h"

%include "BaconBox/Input/InputManager.h"


%include "BaconBox/Components/Visibility.h"
%include "BaconBox/Components/Transform.h"
%include "BaconBox/AxisAlignedBoundingBox.h"
 %include "BaconBox/Components/AABBHitbox.h"
  %include "BaconBox/Components/SizeComponent.h"

%include "BaconBox/Display/ColorFormat.h"


%include "BaconBox/Display/TextureInformation.h"
%include "BaconBox/Display/SubTextureInfo.h"

%include "BaconBox/Components/LineComponent.h"

%include "BaconBox/Components/Timeline.h"
%include "BaconBox/Components/EntityContainer.h"



#if defined(BB_LUA)
%include "BaconBox/Components/Lua/LuaEntity.h"
#endif


%include "BaconBox/Components/MatrixComponent.h"
%include "BaconBox/Helper/Ease.h"

%include "BaconBox/Helper/MathHelper.h"

%include "BaconBox/Helper/TimeHelper.h"
%include "BaconBox/Helper/Stopwatch.h"
%include "BaconBox/Components/Shake.h"
%include "BaconBox/Components/CameraPositionConverter.h"

%include "BaconBox/Display/Camera.h"

%include "BaconBox/Core/State.h"


%immutable BaconBox::Engine::onInitialize;
%include "BaconBox/Core/Engine.h"

%include "BaconBox/Audio/AudioState.h"
%include "BaconBox/Audio/Sound.h"

%include "BaconBox/Audio/AudioEngine.h"
%include "BaconBox/Audio/SoundEngine.h"
%include "BaconBox/Audio/SoundFX.h"

%include "BaconBox/Audio/MusicEngine.h"
%include "BaconBox/Audio/BackgroundMusic.h"
%include "BaconBox/Display/Text/FontFormat.h"

%include "BaconBox/Display/Text/Font.h"

%include "BaconBox/Display/Text/TextAlignment.h"
%include "BaconBox/Symbol.h"
%include "BaconBox/Components/SymbolComponent.h"

%include "BaconBox/Components/TextComponent.h"
%include "BaconBox/Components/Speed.h"

	%include "BaconBox/Display/ParticlePhase.h"
	%include "BaconBox/Display/Particle.h"
	%include "BaconBox/Display/Emitter.h"
	%include "BaconBox/Components/ParticleEmitter.h"
	
%include "BaconBox/MovieClipEntity/MovieClipEntity.h"
	%include "BaconBox/Line.h"

%include "BaconBox/EmitterEntity.h"

%include "BaconBox/Display/Text/TextEntity.h"


%ignore getMovieClipEntityFromSymbol;
%include "BaconBox/EntityFactory.h" 
%include "BaconBox/Helper/EmitterFactory.h"
%include "BaconBox/Display/PixMap.h"

%include "BaconBox/Helper/ResourcePathHandler.h"

%include "BaconBox/LocalizationManager.h"
%include "BaconBox/Audio/MusicParameters.h"

%include "BaconBox/Audio/SoundParameters.h"
%include "BaconBox/ResourceManager.h"
%extend BaconBox::ResourceManager {
  static void unloadAllTextureExcept(lua_State * L){
    lua_pushnil(L);
    std::set<std::string> exceptions;
    while (lua_next(L, -2) != 0) {
      std::string key(lua_tostring (L, -1));
      exceptions.insert(key);
      lua_pop(L, 1);
    }
    BaconBox::ResourceManager::unloadAllTextureExcept(exceptions);

  }

}

namespace BaconBox{
  
  #if !defined (BB_FLASH_PLATFORM)
  class GraphicDriver {
  public:
    static GraphicDriver &getInstance();
    void renderToTexture(const TextureInformation *textureInformation, unsigned int contextWidth = 0, unsigned int contextHeight = 0);
    void endRenderToTexture();
    private:
    GraphicDriver();
    ~GraphicDriver();
  };
  #endif
  



}

