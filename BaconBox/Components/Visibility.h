#ifndef BB_VISIBILITY_H
#define BB_VISIBILITY_H

#include "BaconBox/Core/Component.h"

namespace BaconBox {
	/**
	 * Component that determines its Entity's visibility.
	 */
	class Visibility : public Component {
	public:
		BB_ID_HEADER;
		
		Visibility();
		
		Visibility(const Visibility &src);
		
		virtual ~Visibility();
		
		Visibility &operator=(const Visibility &src);
		
		virtual Visibility *clone() const;
		
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
	private:
	};
}

#endif /* defined(BB_VISIBILITY_H) */