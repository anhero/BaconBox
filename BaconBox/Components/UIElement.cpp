#include "BaconBox/Components/UIManager.h"
#include "BaconBox/Core/IDManager.h"
#include "BaconBox/Core/Component.h"
#include "BaconBox/Components/UIElement.h"


namespace BaconBox {
	BB_ID_IMPL(UIElement);

	UIElement::UIElement() : Component(), manager(NULL) {
		
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
}
