/**
 * @file
 * @ingroup Math
 */

#ifndef BB_MATRIX2D_H
#define BB_MATRIX2D_H

#include "vmath.h"


namespace BaconBox {
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
	
	VMATH_NAMESPACE::Vector2f multiplyWithVector(const VMATH_NAMESPACE::Vector2f & v) const;
	
	Matrix2D & concat(const Matrix2D & m);
	
	void translate(const VMATH_NAMESPACE::Vector2f & v);
	
	void scale(const VMATH_NAMESPACE::Vector2f & v);
	
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
