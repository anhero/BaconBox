#ifndef BB_VISIBILITY_H
#define BB_VISIBILITY_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Property.h"
namespace BaconBox {
	/**
	 * Component that determines its Entity's visibility.
	 */
	class Visibility : public Component {
	public:
		BB_ID_HEADER;
		
		/// Message ID to use when requesting the entity's visibility.
		static int MESSAGE_IS_VISIBLE;
		/// Message ID to use when setting the entity's visibility.
		static int MESSAGE_SET_VISIBLE;
		/// Message ID the component sends when its entity's visibility has changed.
		static int MESSAGE_VISIBILITY_CHANGED;
		
		Visibility();
		
		Visibility(const Visibility &src);
		
		virtual ~Visibility();
		
		Visibility &operator=(const Visibility &src);
		
		virtual Visibility *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		bool isVisible() const;
		
		void setVisible(bool newVisible);
	private:
		/// Determines whether or not the Entity is visible.
		bool visible;
	};
	
	class VisibilityProxy : public ComponentProxy {
	public:
		VisibilityProxy(Entity *entity, bool mustAddComponent = true);
		
		bool isVisible() const;
		void setVisible(bool newVisible);
#ifdef SWIG
		bool visible;
#else
		Property<bool, Visibility> visible;
#endif
	private:
	};
}

#endif /* defined(BB_VISIBILITY_H) */