#ifndef BB_UIELEMENT_H
#define BB_UIELEMENT_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"

namespace BaconBox {
	class UIManager;
	class UIElementProxy;
	class UIElement : public Component {
		friend class UIElementProxy;
		friend class UIManager;
	public:
		BB_ID_HEADER;
		
		UIElement();
		~UIElement();
		
		void addToUIManager(UIManager * uiManager);

		void removeFromUIManager();

		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		void setEnabled(bool isEnabled);
		void enable();
		void disable();
		bool isEnabled();

	protected:
		bool enabled;

	private:
		void removeUIManagerReference();

		UIManager* manager;


	};
	
	class UIElementProxy : public ComponentProxy {
		friend class UIManager;
	public:
		UIElementProxy(Entity *entity, bool mustAddComponent = true);
		void addToUIManager(UIManager * uiManager);
		void removeFromUIManager();

		void setEnabled(bool isEnabled);
		void enable();
		void disable();
		bool isEnabled();

	private:
		void removeUIManagerReference();

	};
}

#endif
