#include "BaconBox/Core/Flash/FlashEngine.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Components/Flash/FlashEntityManager.h"
#include "BaconBox/Core/Engine.h"
namespace BaconBox {
AS3::local::var FlashEngine::stage;

			// package_as3("#package BaconBox\n"
			// 	"import flash.events.Event; \n"
			// 	"function EnginePulseEventListener(event:flash.events.Event):void {BaconBox.Engine.pulse();}\n");

		FlashEngine::FlashEngine():BaseEngine(){
			AS3::local::var activeConsole;
			inline_as3("import flash.display.DisplayObject;\n"
						"import flash.display.Stage;\n"
						"import BaconBox.EnginePulseEventListener;\n"
						"import flash.events.Event; \n"
						"var activeConsole:DisplayObject = (CModule.activeConsole as DisplayObject);\n"
						"var theStage:Stage = activeConsole.stage;\n"
						"activeConsole.addEventListener(flash.events.Event.ENTER_FRAME, function(event:flash.events.Event):void {BaconBox.Engine.pulse();})"
						::);
			AS3_GetVarxxFromVar(stage, theStage);	

		}

		AS3::local::var FlashEngine::getCurrentStateMC(){
			return static_cast<FlashEngine*>(&Engine::getInstance())->currentStateMovieClip;
		} 


		AS3::local::var FlashEngine::getStage(){
			return stage;
		} 

		State *FlashEngine::addState(State *newState){
			BaseEngine::addState(newState);
		}

		void FlashEngine::swapActiveMovieClip(AS3::local::var newMovieClip){
			AS3::local::var args[1];

			if(currentStateMovieClip != AS3::local::internal::_null){
				args[0]  = currentStateMovieClip;
			AS3::local::var containsAS3 = FlashHelper::callMethod(stage, "contains", 1, args);
			bool contains = AS3::local::internal::bool_valueOf(containsAS3);
			if(contains){
				FlashHelper::callMethod(stage, "removeChild", 1, args);
			}				
			}
			currentStateMovieClip = args[0] = newMovieClip;
			FlashHelper::callMethod(stage, "addChild", 1, args);
		}

		void FlashEngine::removeState(const std::string &name){
			State * aState = getState(name);
			AS3::local::var mc= reinterpret_cast<FlashEntityManager*>(aState->getComponent(FlashEntityManager::ID))->getMovieClip();
			AS3::local::var args[1] = {mc};
			AS3::local::var containsAS3 = FlashHelper::callMethod(stage, "contains", 1, args);
			bool contains = AS3::local::internal::bool_valueOf(containsAS3);
			if(contains){
				FlashHelper::callMethod(stage, "removeChild", 1, args);
			}
			BaseEngine::removeState(name);

		}
}
