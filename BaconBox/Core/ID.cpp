#include "ID.h"

namespace BaconBox {
	int IDImplementation::getNextId() {
		static int counter = 0;
		return counter++;
	}
}