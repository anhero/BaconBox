/**
 * @file
 */
#ifndef BB_TEXTFIELDHOLDER_H
#define BB_TEXTFIELDHOLDER_H

#include "../../Core/Component.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {
	/**
	 *
	 */
	class TextFieldHolder  : public Component{
    public:
    	
    	BB_ID_HEADER;
    	
        TextFieldHolder(AS3::local::var aMC);
		void setMovieClip(AS3::local::var aMC);
		void setText(const std::string & text);
		AS3::local::var getMovieClip();
		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
    private:
		AS3::local::var mc;
		AS3::local::var textField;
		AS3::local::var textFormat;

	};
}

#endif // BB_MOVIECLIPCOMPONENT_H