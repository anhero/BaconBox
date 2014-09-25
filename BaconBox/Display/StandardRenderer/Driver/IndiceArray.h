/**
 * @file
 */
#ifndef BB_INDICE_ARRAY_H
#define BB_INDICE_ARRAY_H

#include <stdint.h>

#include <vector>
#include <list>

#include "BaconBox/StandardVertexArray.h"

namespace BaconBox {
	typedef std::vector<uint16_t> IndiceArray;
	typedef std::list<std::pair<StandardVertexArray::SizeType, IndiceArray::size_type> > IndiceArrayList;
}

#endif // BB_INDICE_ARRAY_H
