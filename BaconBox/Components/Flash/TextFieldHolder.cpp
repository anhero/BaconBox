#include "TextFieldHolder.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Components/TextComponent.h"


#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/Vector2ChangedData.h"

#include "BaconBox/Display/Text/Flash/FlashFont.h"

namespace BaconBox {

	BB_ID_IMPL(TextFieldHolder);
	

	TextFieldHolder::TextFieldHolder(AS3::local::var aMC) : Component(){
		setMovieClip(aMC);
	}

	void TextFieldHolder::setMovieClip(AS3::local::var aMC){
		mc = aMC;
		AS3::local::var args[1] = {AS3::local::internal::new_String("text")};
		textField = FlashHelper::callMethod(mc, "getChildByName", 1, args);
		textFormat = FlashHelper::getProperty(textField, "defaultTextFormat");
	}

	void TextFieldHolder::createFontFromTextField(){
		Console__error("TextFieldHolder::createFontFromTextField is not fully implemented yet.");
		 char *str = NULL;
	    AS3_MallocString(str, FlashHelper::getProperty(font, "font"));
	    std::string fontName(str);
	    free(str);
		FlashFont * font = new FlashFont(fontName);
		reinterpret_cast<TextEntity*>(getEntity())->setFont(font);
	}

	void TextFieldHolder::setText(const std::string & text){
		FlashHelper::setProperty(textField, "text", AS3::local::internal::new_String(text.c_str()));
	}

	
	AS3::local::var TextFieldHolder::getMovieClip(){
		return mc;
	}

	void TextFieldHolder::setAlignment(TextAlignment::type alignment){
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

	void TextFieldHolder::setColor(const Color &newColor){
		color = newColor;
		unsigned int colorValue = color.getRGB();
		FlashHelper::setProperty(textField, "textColor", AS3::local::internal::new_uint(colorValue));
	}

	void TextFieldHolder::receiveMessage(int senderID, int destID, int message, void *data){
		 if(destID != Entity::BROADCAST && destID != TextFieldHolder::ID ) return;

		 if(senderID == Transform::ID){
		 	if(message == Transform::MESSAGE_POSITION_CHANGED)	{
				Vector2ChangedData * pos = (reinterpret_cast<Vector2ChangedData *>(data));
				FlashHelper::setProperty(mc, "x", AS3::local::internal::new_int(pos->newValue.x));
				FlashHelper::setProperty(mc, "y", AS3::local::internal::new_int(pos->newValue.y));
		 	}	
		 	else if(message == Transform::MESSAGE_ROTATION_CHANGED){
		 		ValueChangedData<float>* rotation= reinterpret_cast<ValueChangedData<float>*>(data);
		 		FlashHelper::setProperty(mc, "rotation", AS3::local::internal::new_Number(rotation->newValue));
		 	}
		 	else if(message == Transform::MESSAGE_SCALE_CHANGED){
		 		Vector2ChangedData * scale = (reinterpret_cast<Vector2ChangedData *>(data));
		 		FlashHelper::setProperty(mc, "scaleX", AS3::local::internal::new_Number(scale->newValue.x));
				FlashHelper::setProperty(mc, "scaleY", AS3::local::internal::new_Number(scale->newValue.y));
		 	}	
		 }
		 else if(senderID == TextComponent::ID){
			if(message == TextComponent::MESSAGE_TEXT_CHANGED ){
				setText(*reinterpret_cast<std::string*>(data));
			}
			else if(message == TextComponent::MESSAGE_SIZE_CHANGED){
			    Vector2 & size = reinterpret_cast<AxisAlignedBoundingBox*>(data)->getSize();
			    FlashHelper::setProperty(textField, "width", AS3::local::internal::new_Number(size.x));
				FlashHelper::setProperty(textField, "height", AS3::local::internal::new_Number(size.y));
			}
			else if(message == TextComponent::MESSAGE_ALIGNMENT_CHANGED ){
			    setAlignment(*reinterpret_cast<TextAlignment::type*>(data));
			}
		}
		else if(senderID == ColorFilter::ID){
			if(message == ColorFilter::MESSAGE_COLOR_CHANGED ){
				setColor(*reinterpret_cast<Color*>(data));
			}
		}
		else if(senderID == TextEntity::ID){
		if(message == Entity::MESSAGE_ADDING_COMPONENT){
			setColor(reinterpret_cast<ColorFilter*>(getEntity()->getComponent(ColorFilter::ID))->getColor());
		}
	}
	}
    
}