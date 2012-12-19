/**
 * @file
 */
#ifndef BB_MOVIECLIPHOLDER_H
#define BB_MOVIECLIPHOLDER_H

#include "../../Core/Component.h"

#include <AS3/AS3.h>
#include <Flash++.h>

namespace BaconBox {
	/**
	 *
	 */
	class MovieClipHolder  : public Component{
    public:
        MovieClipHolder(AS3::local::var aMC);
		void setMovieClip(AS3::local::var aMC);
		AS3::local::var getMovieCLip();
		
    private:
		AS3::local::var mc;
		
	};
}

#endif // BB_MOVIECLIPCOMPONENT_H