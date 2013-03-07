/**
 * @file
 * @ingroup Math
 */

#ifndef BB_MATRIX_H
#define BB_MATRIX_H

#include "Vector2.h"


namespace BaconBox {
    struct Matrix{
	float a;
	float b;
	float c;
	float d;
	float tx;
	float ty;
	Matrix();
	Matrix(float a, float b, float c, float d, float tx, float ty);
	Matrix(const Matrix &src);
	
	Matrix &operator=(const Matrix &src);

	
	Matrix operator*(const Matrix & m) const;
	

	
	Matrix &operator*=(const Matrix& m);
	
	
	bool isSkewed() const;
	
	Vector2 multiplyWithVector(const Vector2 & v) const;
	
	void concat(const Matrix & m);
	
	void translate(const Vector2 & v);
	
	void scale(const Vector2 & v);
	
	void rotate(float angle);
	void serialize(Value &node, bool setName = true) const;

		
	bool deserialize(const Value &node);

	static bool isValidValue(const Value &node);	
	friend  std::ostream &operator<<(std::ostream &output, const Matrix& m);
    };
    
	
    
}

#endif
