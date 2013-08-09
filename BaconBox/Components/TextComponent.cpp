#include "TextComponent.h"

#include "BaconBox/Core/Entity.h"
#include "BaconBox/Console.h"
#include "BaconBox/Helper/StringHelper.h"
#include "BaconBox/Helper/UTFConvert.h"
#include "BaconBox/EntityFactory.h"
#include "Mesh.h"
#include "BaconBox/Display/Text/Font.h"
#include "BaconBox/Core/Engine.h"
#include "BaconBox/Display/Text/TextAlignment.h"
#include "BaconBox/Helper/Vector2ChangedData.h"

#ifdef BB_FLASH_PLATFORM
#include "BaconBox/Components/Flash/TextFieldHolder.h"
#endif

#include "BaconBox/Script/Lua/LuaManager.h"

namespace BaconBox {
	int TextComponent::MESSAGE_TEXT_CHANGED = IDManager::generateID();
	int TextComponent::MESSAGE_FONT_CHANGED = IDManager::generateID();
	int TextComponent::MESSAGE_ALIGNMENT_CHANGED = IDManager::generateID();
	int TextComponent::MESSAGE_SIZE_CHANGED = IDManager::generateID();

	BB_ID_IMPL(TextComponent);

	TextComponent::TextComponent() : Component(), alignment(TextAlignment::LEFT), boundingBox(Vector2(), Vector2(200, 200)) {
	}

	TextComponent::~TextComponent() {
	}

	void TextComponent::receiveMessage(int senderID, int destID, int message, void *data) {
		if (senderID == Transform::ID) {
			if (message == Transform::MESSAGE_POSITION_CHANGED) {
				boundingBox.setPosition(reinterpret_cast<Vector2ChangedData *>(data)->newValue);
			}
		}
	}

	void TextComponent::setAlignment(TextAlignment::type alignment) {
		this->alignment = alignment;
		sendMessage(Entity::BROADCAST, TextComponent::MESSAGE_ALIGNMENT_CHANGED, reinterpret_cast<void *>(&alignment));
	}

	void TextComponent::setSize(Vector2 size) {
		boundingBox.setSize(size);
		sendMessage(Entity::BROADCAST, TextComponent::MESSAGE_SIZE_CHANGED, reinterpret_cast<void *>(&boundingBox));
	}

	const std::string & TextComponent::getText() const{
		return text;
	}
	
	void TextComponent::setText(const std::string &text) {
	    #ifdef BB_DEBUG
		try{
        #endif

		this->text = text;

		sendMessage(Entity::BROADCAST, TextComponent::MESSAGE_TEXT_CHANGED, reinterpret_cast<void *>(&this->text));


        #ifdef BB_DEBUG
		}
		catch(...){
        #ifdef BB_LUA
        LuaManager::getDefault().error("PREPUCE?!?!");
        #endif
		Console__error("Error calling TextComponent::setText");

		}
	#endif

	}

	const Vector2 &TextComponent::getSize() {
		return boundingBox.getSize();
	}

	void TextComponent::setFont(Font *font) {
		this->font = font;
		sendMessage(Entity::BROADCAST, TextComponent::MESSAGE_FONT_CHANGED, reinterpret_cast<void *>(font));
	}

	Font *TextComponent::getFont() {

#ifdef BB_FLASH_PLATFORM

		if (font == NULL) {
			reinterpret_cast<TextFieldHolder *>(getEntity()->getComponent(TextFieldHolder::ID))->createFontFromTextField();
		}

#endif

		return font;
	}

	TextComponentProxy::TextComponentProxy(Entity *entity, Font *font, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new TextComponent()), text(this, &TextComponentProxy::getText, &TextComponentProxy::setText)  {
		reinterpret_cast<TextComponent *>(component)->font = font;
	}

	void TextComponentProxy::setAlignment(TextAlignment::type alignment) {
		reinterpret_cast<TextComponent *>(component)->setAlignment(alignment);
	}

	void TextComponentProxy::setFont(Font *font) {
		reinterpret_cast<TextComponent *>(component)->setFont(font);
	}

	Font *TextComponentProxy::getFont() {
		return reinterpret_cast<TextComponent *>(component)->getFont();
	}

	const Vector2   &TextComponentProxy::getSize() {
		return reinterpret_cast<TextComponent *>(component)->getSize();
	}

	void TextComponentProxy::setSize(Vector2 size) {
		reinterpret_cast<TextComponent *>(component)->setSize(size);
	}

	void TextComponentProxy::setText(const std::string &text) {
		reinterpret_cast<TextComponent *>(component)->setText(text);
	}
	
	const std::string & TextComponentProxy::getText() const{
		return reinterpret_cast<TextComponent *>(component)->getText();

	}


}
