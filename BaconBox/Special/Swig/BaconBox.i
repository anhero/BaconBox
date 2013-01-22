
%module BaconBox

%{
	
	#ifdef BB_FLASH_PLATEFORM
	#include <AS3/AS3.h>
	#include <AS3/AS3++.h>
	#endif


	#include "BaconBox/Core/Component.h"
	#include "BaconBox/Core/Entity.h"

	#include "BaconBox/Vector2.h"
	#include "BaconBox/Components/Transform.h"
	#include "BaconBox/Components/Flash/MovieClipHolder.h" 

	#include "BaconBox/MovieClipEntity/MovieClipEntity.h"

%}

#ifdef BB_FLASH_PLATEFORM


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


%include "BaconBox/Core/Component.h"

%include "BaconBox/Core/Entity.h"

//%include "BaconBox/Vector2.h"

namespace BaconBox{
	class Vector2{
		public:
		Vector2();

		float x;
		float y;
	};
}


%include "BaconBox/Components/Transform.h"


%include "BaconBox/Components/Flash/MovieClipHolder.h"


%include "BaconBox/MovieClipEntity/MovieClipEntity.h"


