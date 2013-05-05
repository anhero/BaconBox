#include "BaconBox/Vector3.h"

namespace BaconBox {
	template <> const float Vector<float, 3u>::ONE = 1.0f;
	template <> const double Vector<double, 3u>::ONE = 1.0;
	template <> const long double Vector<long double, 3u>::ONE = 1.0l;
	
	template <> const Vector<float, 3u> Vector<float, 3u>::UP(0.0f, -ONE, 0.0f);
	template <> const Vector<double, 3u> Vector<double, 3u>::UP(0.0, -ONE, 0.0);
	template <> const Vector<long double, 3u> Vector<long double, 3u>::UP(0.0l, -ONE, 0.0l);
	
	template <> const float Vector<float, 3u>::ZERO = 0.0f;
	template <> const double Vector<double, 3u>::ZERO = 0.0;
	template <> const long double Vector<long double, 3u>::ZERO = 0.0l;
}
