/**
 * @file
 */
#ifndef BB_LINE_H
#define BB_LINE_H

#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
#include "BaconBox/Components/LineComponent.h"
namespace BaconBox {
	/**
	 *
	 */
	class Line : public MovieClipEntity, public LineComponentProxy
    {
    public:
		BB_ID_HEADER;

		Line(const std::string & patternKey);
		Line(const Line& src);
		
		virtual ~Line();
		
		Line &operator=(const Line &src);


    private:


	};
}

#endif // BB_LINE_H
