#include "FlashTextManager.h"


#include "BaconBox/Components/Flash/MovieClipHolder.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Helper/Vector2ChangedData.h"
#include "BaconBox/Components/TextComponent.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Components/Visibility.h"
#include "BaconBox/Console.h"

namespace BaconBox {

	BB_ID_IMPL(FlashTextManager);


	FlashTextManager::FlashTextManager() : Component(), movieClipHolder(NULL), textField(AS3::local::internal::_null){
			this->initializeConnections();
	}

	FlashTextManager::~FlashTextManager(){}

	void FlashTextManager::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
		this->refreshConnections();
	}

	void FlashTextManager::setText(const std::string & text){
		FlashHelper::setProperty(textField, "text", AS3::local::internal::new_String(text.c_str()));
	}


	void FlashTextManager::setAlignment(TextAlignment::type alignment){

		AS3::local::var textFormat = FlashHelper::getProperty(textField, "defaultTextFormat");

		inline_as3("import flash.text.TextFormatAlign;");
		AS3::local::var flashAlignment;
		if(alignment == TextAlignment::LEFT){
			AS3_GetVarxxFromVar(flashAlignment, TextFormatAlign.LEFT);
		}
		else if(alignment == TextAlignment::CENTER){
			AS3_GetVarxxFromVar(flashAlignment, TextFormatAlign.CENTER);
		}
		else if(alignment == TextAlignment::RIGHT){
			AS3_GetVarxxFromVar(flashAlignment, TextFormatAlign.RIGHT);
		}
			FlashHelper::setProperty(textFormat, "align", flashAlignment);
			FlashHelper::setProperty(textField, "defaultTextFormat", textFormat);
			setColor(color);
	}

	void FlashTextManager::setColor(const Color &newColor){
		color = newColor;
		unsigned int colorValue = color.getRGB();
		FlashHelper::setProperty(textField, "textColor", AS3::local::internal::new_uint(colorValue));
	}



	void FlashTextManager::receiveMessage(int senderID, int destID, int message, void *data){
		Component::receiveMessage(senderID, destID, message, data);
		 if(destID != Entity::BROADCAST && destID != FlashTextManager::ID ) return;
		 		 if(senderID == TextComponent::ID){
			if(message == TextComponent::MESSAGE_TEXT_CHANGED ){
				setText(*reinterpret_cast<std::string*>(data));
			}
			else if(message == TextComponent::MESSAGE_SIZE_CHANGED){
			    Vector2 & size = reinterpret_cast<AABB*>(data)->getSize();
			    FlashHelper::setProperty(textField, "width", AS3::local::internal::new_Number(size.x));
				FlashHelper::setProperty(textField, "height", AS3::local::internal::new_Number(size.y));
			}
			else if(message == TextComponent::MESSAGE_ALIGNMENT_CHANGED ){
			    setAlignment(*reinterpret_cast<TextAlignment::type*>(data));
			}	
		}
		else if(senderID == ColorTransform::ID){
			if(message == ColorTransform::MESSAGE_COLOR_CHANGED ){
				setColor(*reinterpret_cast<Color*>(data));
			}
		}
		else if(senderID == MovieClipHolder::ID){
		 	if(message == MovieClipHolder::MESSAGE_SET_MOVIECLIP ){
		 			AS3::local::var args[1] = {AS3::local::internal::new_String("text")};
					textField = FlashHelper::callMethod(*reinterpret_cast<AS3::local::var*>(data), "getChildByName", 1, args);
		 	}
		 }

	}



}
