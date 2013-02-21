#include "TextFieldHolder.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/TextComponent.h"


#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/Vector2ChangedData.h"

namespace BaconBox {

	BB_ID_IMPL(TextFieldHolder);
	

	TextFieldHolder::TextFieldHolder(AS3::local::var aMC) : Component(){
		setMovieClip(aMC);
	}

	void TextFieldHolder::setMovieClip(AS3::local::var aMC){
		mc = aMC;
		AS3::local::var args[1] = {AS3::local::internal::new_String("text")};
		textField = FlashHelper::callMethod(mc, "getChildByName", 1, args);
	}

	void TextFieldHolder::setText(const std::string & text){
		FlashHelper::setProperty(textField, "text", AS3::local::internal::new_String(text.c_str()));
	}

	
	AS3::local::var TextFieldHolder::getMovieClip(){
		return mc;
	}

	void TextFieldHolder::receiveMessage(int senderID, int destID, int message, void *data){
		 if(destID != Entity::BROADCAST && destID != TextFieldHolder::ID ) return;

		 if(senderID == Transform::ID){
		 	if(message == Transform::MESSAGE_POSITION_CHANGED)	{
				Vector2ChangedData * pos = (reinterpret_cast<Vector2ChangedData *>(data));
		 	}	
		 	else if(message == Transform::MESSAGE_ROTATION_CHANGED){
		 		ValueChangedData<float>* rotation= reinterpret_cast<ValueChangedData<float>*>(data);

		 	}
		 	else if(message == Transform::MESSAGE_SCALE_CHANGED){
		 		Vector2ChangedData * scale = (reinterpret_cast<Vector2ChangedData *>(data));
		 	}	
		 }
		 else if(senderID == TextComponent::ID){
			if(message == TextComponent::MESSAGE_TEXT_CHANGED ){
				setText(*reinterpret_cast<std::string*>(data));
			}
		}

	}
    
}