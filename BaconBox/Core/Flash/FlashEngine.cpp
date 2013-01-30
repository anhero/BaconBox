#include "BaconBox/Core/Flash/FlashEngine.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Components/Flash/FlashEntityManager.h"

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
			AS3::local::var mc= reinterpret_cast<FlashEntityManager*>(newState->getComponent(FlashEntityManager::ID))->getMovieClip();
			AS3::local::var args[1] = {mc};
			FlashHelper::callMethod(stage, "addChild", 1, args);

		}

		void FlashEngine::removeState(const std::string &name){
			State * aState = getState(name);
			AS3::local::var mc= reinterpret_cast<FlashEntityManager*>(aState->getComponent(FlashEntityManager::ID))->getMovieClip();
			AS3::local::var args[1] = {mc};
			FlashHelper::callMethod(stage, "removeChild", 1, args);
			BaseEngine::removeState(name);

		}
}
