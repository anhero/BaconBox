/**
 * @file
 */
#ifndef BB_MOVIECLIPHOLDER_H
#define BB_MOVIECLIPHOLDER_H

#include "../../Core/Component.h"

#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {
	/**
	 *
	 */
	class MovieClipHolder  : public Component{
    public:
    	static int ID;

    	virtual int getID() const;
    	
        MovieClipHolder(AS3::local::var aMC);
		void setMovieClip(AS3::local::var aMC);
		AS3::local::var getMovieClip();

		void setProperty(const std::string & propertyName, AS3::local::var arg);

		AS3::local::var getProperty(const std::string & propertyName);


		AS3::local::var callMethod(const std::string & functionName, int argCount, AS3::local::var *args);

		virtual void receiveMessage(int senderID, int destID, int message, void *data);
		
    private:
		AS3::local::var mc;
		
	};
}

#endif // BB_MOVIECLIPCOMPONENT_H