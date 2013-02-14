#include "TextComponent.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "Helper/StringHelper.h"
#include "Helper/UTFConvert.h"
#include "EntityFactory.h"
#include "Mesh.h"
#include "BaconBox/Display/Text/Font.h"
#include "Core/Engine.h"
namespace BaconBox {
    
	int TextComponent::MESSAGE_TEXT_CHANGED = IDManager::generatetID();
	
	BB_ID_IMPL(TextComponent);
	
	TextComponent::TextComponent() : Component() {
	}

	TextComponent::~TextComponent() {
	}
	


	void TextComponent::receiveMessage(int senderID, int destID, int message, void *data) {
	    
	}
	
	
	void TextComponent::setText(const std::string & text){
	    std::string temp = text;
	    sendMessage(Entity::BROADCAST, TextComponent::MESSAGE_TEXT_CHANGED, reinterpret_cast<void*>(&temp));
	}
	
	Font * TextComponent::getFont(){
	    return font;
	}
	
	TextComponentProxy::TextComponentProxy(Entity* entity, Font * font, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new TextComponent())  {
	    reinterpret_cast<TextComponent*>(component)->font = font;
	}
	    
	Font * TextComponentProxy::getFont(){
	    return reinterpret_cast<TextComponent*>(component)->getFont();
	}
	void TextComponentProxy::setText(const std::string & text){
	    reinterpret_cast<TextComponent*>(component)->setText(text);
	}
	
}