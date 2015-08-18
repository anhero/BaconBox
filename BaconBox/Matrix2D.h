/**
 * @file
 * @ingroup Math
 */

#ifndef BB_MATRIX2D_H
#define BB_MATRIX2D_H

#include "Vector2.h"


namespace BaconBox {
	/*
	 * The 2D matrix	 is only affected by those components
	 * in the transformation matrix:
	 * ┌        ┐
	 * │ a b tx │
	 * │ c d ty │
	 * │ 0 0 1  │
	 * └        ┘
	 *  see: http://help.adobe.com/en_US/AS2LCR/Flash_10.0/help.html?content=00001227.html#332312
	 */
    struct Matrix2D{
	float a;
	float b;
	float c;
	float d;
	float tx;
	float ty;
	Matrix2D();
	Matrix2D(float a, float b, float c, float d, float tx, float ty);
	Matrix2D(const Matrix2D &src);
	
	Matrix2D &operator=(const Matrix2D &src);

	
	Matrix2D operator*(const Matrix2D & m) const;
	

	
	Matrix2D &operator*=(const Matrix2D& m);
	
	
//	bool isSkewed() const;
	
	Vector2 multiplyWithVector(const Vector2 & v) const;
	
	Matrix2D & concat(const Matrix2D & m);
	
	void translate(const Vector2 & v);
	
	void scale(const Vector2 & v);
	
	void rotate(float angle);
	void serialize(Value &node, bool setName = true) const;

		
	bool deserialize(const Value &node);

	static bool isValidValue(const Value &node);
#ifndef SWIG
	friend  std::ostream &operator<<(std::ostream &output, const Matrix2D& m);
#endif
    };
    
	
    
}

#endif
