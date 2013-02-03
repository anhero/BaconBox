#ifndef BB_COLOR_FILTER_H
#define BB_COLOR_FILTER_H

#include "BaconBox/Core/Component.h"
#include "BaconBox/Display/Color.h"

namespace BaconBox {
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
		
		const Color &getColor() const;
		
		void setColor(const Color &newColor);
	private:
		Color color;
	};
}

#endif /* defined(BB_COLOR_FILTER_H) */
