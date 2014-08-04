#include "BaconBox/Components/UIManager.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/Components/UIElement.h"


namespace BaconBox {
	BB_ID_IMPL(UIElement);

	UIElement::UIElement() : Component(), manager(NULL), enabled(true) {
		
	}
		
	UIElement::~UIElement(){
		removeFromUIManager();
	}
	
	void UIElement::receiveMessage(int senderID, int destID, int message, void *data) {
		Component::receiveMessage(senderID, destID, message, data);
	}
	
	void UIElement::addToUIManager(UIManager * uiManager){
		manager = uiManager;
	}
	
	void UIElement::removeFromUIManager(){
		if(manager){
			manager->removeClickable(getEntity<MovieClipEntity>());
		}
	}
	void UIElement::removeUIManagerReference(){
		if(manager){
			manager = NULL;
		}
	}
	
	void UIElement::setEnabled (bool isEnabled) {
		this->enabled = isEnabled;
	}
	void UIElement::disable() {
		this->enabled = false;
	}
	void UIElement::enable() {
		this->enabled = true;
	}
	bool UIElement::isEnabled() {
		return this->enabled;
	}


	UIElementProxy::UIElementProxy(Entity* entity, bool mustAddComponent): BB_PROXY_CONSTRUCTOR(new UIElement())  {
	}


	void UIElementProxy::addToUIManager(UIManager * uiManager){
	    reinterpret_cast<UIElement*>(component)->addToUIManager(uiManager);
	}
	
	void UIElementProxy::removeFromUIManager(){
	    reinterpret_cast<UIElement*>(component)->removeFromUIManager();
	}
	void UIElementProxy::removeUIManagerReference(){
	    reinterpret_cast<UIElement*>(component)->removeUIManagerReference();
	}

	void UIElementProxy::setEnabled(bool isEnabled) {
		reinterpret_cast<UIElement*>(component)->setEnabled(isEnabled);
	}
	void UIElementProxy::disable() {
		reinterpret_cast<UIElement*>(component)->disable();
	}
	void UIElementProxy::enable() {
		reinterpret_cast<UIElement*>(component)->enable();
	}
	bool UIElementProxy::isEnabled() {
		return reinterpret_cast<UIElement*>(component)->isEnabled();
	}
}
