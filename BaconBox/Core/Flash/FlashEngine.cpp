#include "BaconBox/Core/Flash/FlashEngine.h"


namespace BaconBox {

		FlashEngine::FlashEngine():BaseEngine(){
			AS3::local::var activeConsole;
			inline_as3("import flash.display.DisplayObject;\n"
						"import flash.display.Stage;\n"
						"var activeConsole:DisplayObject = (CModule.activeConsole as DisplayObject);\n"
						"var theStage:Stage = activeConsole.stage;\n"
						::);
			AS3_GetVarxxFromVar(stage, theStage);			
		}

		State *FlashEngine::addState(State *newState){
			BaseEngine::addState(newState);
		}

		void FlashEngine::removeState(const std::string &name){
			BaseEngine::removeState(name);
		}
}
