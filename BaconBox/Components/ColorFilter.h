#ifndef BB_COLOR_FILTER_H
#define BB_COLOR_FILTER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/Color.h"

namespace BaconBox {
	/**
	 * Applies a color to its entity when rendered..
	 */
	class ColorFilter : public Component {
	public:
		BB_ID_HEADER;
		
		static int MESSAGE_GET_COLOR;
		static int MESSAGE_SET_COLOR;
		
		ColorFilter();
		
		ColorFilter(const Color &newColor);
		
		ColorFilter(const ColorFilter &src);
		
		virtual ~ColorFilter();
		
		ColorFilter &operator=(const ColorFilter &src);
		
		virtual ColorFilter *clone() const;
		
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
		/**
		 * Gets the color.
		 * @return Color to apply to the component's entity.
		 */
		const Color &getColor() const;
		
		/**
		 * Sets the color.
		 * @param newColor New color to apply to the component's entity.
		 */
		void setColor(const Color &newColor);
	private:
		/// Color to apply to the component's entity.
		Color color;
	};
}

#endif /* defined(BB_COLOR_FILTER_H) */
