
#ifndef BB_COLOR_MATRIX_H
#define BB_COLOR_MATRIX_H

#include <vector>
#include "BaconBox/Display/Color.h"


namespace BaconBox {
    struct ColorMatrix{

    std::vector<float> matrix;

	ColorMatrix();
	ColorMatrix(float redMultiplier, float redOffset, float greenMultiplier, float greenOffset,
                float blueMultiplier, float blueOffset, float alphaMultiplier, float alphaOffset);
	ColorMatrix(const ColorMatrix &src);

	ColorMatrix &operator=(const ColorMatrix &src);


	ColorMatrix operator*(const ColorMatrix & m) const;



	ColorMatrix &operator*=(const ColorMatrix& m);



	Color multiplyWithColor(const Color & c) const;

	ColorMatrix & concat(const ColorMatrix & parent);



	void setAlphaMultiplier(float alpha);

	void serialize(Value &node, bool setName = true) const;

	bool deserialize(const Value &node);

	friend  std::ostream &operator<<(std::ostream &output, const ColorMatrix& m);
    };



}

#endif
