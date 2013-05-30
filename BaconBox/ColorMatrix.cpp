#include "ColorMatrix.h"

#include "BaconBox/Helper/Serialization/Array.h"
#include "BaconBox/Helper/Serialization/Object.h"

#include "BaconBox/Helper/Serialization/Value.h"
#include "BaconBox/Helper/Serialization/DefaultSerializer.h"
#include "BaconBox/Helper/Serialization/Serializer.h"

#include "BaconBox/Helper/MathHelper.h"
namespace BaconBox {

	ColorMatrix::ColorMatrix():colorOffset(Color::TRANSPARENT), colorMultiplier(Color::WHITE) {
//        matrix[0] = 1;
//        matrix[6] = 1;
//        matrix[12] = 1;
//        matrix[18] = 1;
		
	}

	ColorMatrix::ColorMatrix(float redMultiplier, float redOffset, float greenMultiplier, float greenOffset,
                float blueMultiplier, float blueOffset, float alphaMultiplier, float alphaOffset):
	colorMultiplier(redMultiplier, greenMultiplier, blueMultiplier, alphaMultiplier),
	colorOffset(redOffset, greenOffset, blueOffset, alphaOffset){
//                matrix[0] = redMultiplier;
//                matrix[4] = redOffset;
//
//                matrix[6] = greenMultiplier;
//                matrix[9] = greenOffset;
//
//                matrix[12] = blueMultiplier;
//                matrix[14] = blueOffset;
//
//                matrix[18] = alphaMultiplier;
//                matrix[19] = alphaOffset;
    }

    ColorMatrix::ColorMatrix(const ColorMatrix &src):colorOffset(src.colorOffset), colorMultiplier(src.colorMultiplier){
     
	}

	ColorMatrix &ColorMatrix::operator=(const ColorMatrix &src) {
	    colorMultiplier = src.colorMultiplier;
	    colorOffset = src.colorOffset;
		return *this;
	}


	ColorMatrix ColorMatrix::operator*(const ColorMatrix & m) const{
	    ColorMatrix temp;

//	    temp.matrix[0] = (matrix[0] * m.matrix[0]) + (matrix[1] * m.matrix[5]) + (matrix[2] * m.matrix[10]) + (matrix[3] * m.matrix[15]);
//	    temp.matrix[1] = (matrix[0] * m.matrix[1]) + (matrix[1] * m.matrix[6]) + (matrix[2] * m.matrix[11]) + (matrix[3] * m.matrix[16]);
//	    temp.matrix[2] = (matrix[0] * m.matrix[2]) + (matrix[1] * m.matrix[7]) + (matrix[2] * m.matrix[12]) + (matrix[3] * m.matrix[17]);
//	    temp.matrix[3] = (matrix[0] * m.matrix[3]) + (matrix[1] * m.matrix[8]) + (matrix[2] * m.matrix[13]) + (matrix[3] * m.matrix[18]);
//	    temp.matrix[4] = (matrix[0] * m.matrix[4]) + (matrix[1] * m.matrix[9]) + (matrix[2] * m.matrix[14]) + (matrix[3] * m.matrix[19]) + (matrix[4]);
//
//	    temp.matrix[5] = (matrix[5] * m.matrix[0]) + (matrix[6] * m.matrix[5]) + (matrix[7] * m.matrix[10]) + (matrix[8] * m.matrix[15]);
//	    temp.matrix[6] = (matrix[5] * m.matrix[1]) + (matrix[6] * m.matrix[6]) + (matrix[7] * m.matrix[11]) + (matrix[8] * m.matrix[16]);
//	    temp.matrix[7] = (matrix[5] * m.matrix[2]) + (matrix[6] * m.matrix[7]) + (matrix[7] * m.matrix[12]) + (matrix[8] * m.matrix[17]);
//	    temp.matrix[8] = (matrix[5] * m.matrix[3]) + (matrix[6] * m.matrix[8]) + (matrix[7] * m.matrix[13]) + (matrix[8] * m.matrix[18]);
//	    temp.matrix[9] = (matrix[5] * m.matrix[4]) + (matrix[6] * m.matrix[9]) + (matrix[7] * m.matrix[14]) + (matrix[8] * m.matrix[19]) + (matrix[9]);
//
//	    temp.matrix[10] = (matrix[10] * m.matrix[0]) + (matrix[11] * m.matrix[5]) + (matrix[12] * m.matrix[10]) + (matrix[13] * m.matrix[15]);
//	    temp.matrix[11] = (matrix[10] * m.matrix[1]) + (matrix[11] * m.matrix[6]) + (matrix[12] * m.matrix[11]) + (matrix[13] * m.matrix[16]);
//	    temp.matrix[12] = (matrix[10] * m.matrix[2]) + (matrix[11] * m.matrix[7]) + (matrix[12] * m.matrix[12]) + (matrix[13] * m.matrix[17]);
//	    temp.matrix[13] = (matrix[10] * m.matrix[3]) + (matrix[11] * m.matrix[8]) + (matrix[12] * m.matrix[13]) + (matrix[13] * m.matrix[18]);
//	    temp.matrix[14] = (matrix[10] * m.matrix[4]) + (matrix[11] * m.matrix[9]) + (matrix[12] * m.matrix[14]) + (matrix[13] * m.matrix[19]) + (matrix[14]);
//
//	    temp.matrix[15] = (matrix[15] * m.matrix[0]) + (matrix[16] * m.matrix[5]) + (matrix[17] * m.matrix[10]) + (matrix[18] * m.matrix[15]);
//	    temp.matrix[16] = (matrix[15] * m.matrix[1]) + (matrix[16] * m.matrix[6]) + (matrix[17] * m.matrix[11]) + (matrix[18] * m.matrix[16]);
//	    temp.matrix[17] = (matrix[15] * m.matrix[2]) + (matrix[16] * m.matrix[7]) + (matrix[17] * m.matrix[12]) + (matrix[18] * m.matrix[17]);
//	    temp.matrix[18] = (matrix[15] * m.matrix[3]) + (matrix[16] * m.matrix[8]) + (matrix[17] * m.matrix[13]) + (matrix[18] * m.matrix[18]);
//	    temp.matrix[19] = (matrix[15] * m.matrix[4]) + (matrix[16] * m.matrix[9]) + (matrix[17] * m.matrix[14]) + (matrix[18] * m.matrix[19]) + (matrix[19]);


		temp.colorMultiplier.setRGBA(
								MathHelper::clamp((colorMultiplier.getRed() * m.colorMultiplier.getRed()), -1.0f, 1.0f),
								MathHelper::clamp((colorMultiplier.getGreen() * m.colorMultiplier.getGreen()), -1.0f, 1.0f),
								MathHelper::clamp((colorMultiplier.getBlue() * m.colorMultiplier.getBlue()), -1.0f, 1.0f),
								MathHelper::clamp((colorMultiplier.getAlpha() * m.colorMultiplier.getAlpha()), -1.0f, 1.0f));
		
 
		temp.colorOffset.setRGBA(MathHelper::clamp((colorOffset.getRed() * m.colorMultiplier.getRed()) + m.colorOffset.getRed(), -1.0f, 1.0f),
								 MathHelper::clamp((colorOffset.getGreen() *  m.colorMultiplier.getGreen()) + m.colorOffset.getGreen(), -1.0f, 1.0f),
								 MathHelper::clamp((colorOffset.getBlue() *  m.colorMultiplier.getBlue()) + m.colorOffset.getBlue(), -1.0f, 1.0f),
								 MathHelper::clamp((colorOffset.getAlpha() *  m.colorMultiplier.getAlpha()) + m.colorOffset.getAlpha(), -1.0f, 1.0f));

	    return temp;
	}



	ColorMatrix &ColorMatrix::operator*=(const ColorMatrix& m) {
		colorMultiplier.setRGBA(
									 MathHelper::clamp((colorMultiplier.getRed() * m.colorMultiplier.getRed()), -1.0f, 1.0f),
									 MathHelper::clamp((colorMultiplier.getGreen() * m.colorMultiplier.getGreen()), -1.0f, 1.0f),
									 MathHelper::clamp((colorMultiplier.getBlue() * m.colorMultiplier.getBlue()), -1.0f, 1.0f),
									 MathHelper::clamp((colorMultiplier.getAlpha() * m.colorMultiplier.getAlpha()), -1.0f, 1.0f));
		
		
		colorOffset.setRGBA(MathHelper::clamp((colorOffset.getRed() * m.colorMultiplier.getRed()) + m.colorOffset.getRed(), -1.0f, 1.0f),
								 MathHelper::clamp((colorOffset.getGreen() *  m.colorMultiplier.getGreen()) + m.colorOffset.getGreen(), -1.0f, 1.0f),
								 MathHelper::clamp((colorOffset.getBlue() *  m.colorMultiplier.getBlue()) + m.colorOffset.getBlue(), -1.0f, 1.0f),
								 MathHelper::clamp((colorOffset.getAlpha() *  m.colorMultiplier.getAlpha()) + m.colorOffset.getAlpha(), -1.0f, 1.0f));
		return (*this);
	}

	ColorMatrix & ColorMatrix::concat(const ColorMatrix & parent){
	    (*this) = parent * (*this);
	    return (*this);
	}


	void ColorMatrix::setAlphaMultiplier(float alpha){
        colorMultiplier.setAlpha(alpha);
	}


    Color ColorMatrix::getPreMultipliedColor(const Color & c) const{
	    return c * colorMultiplier;
	}


	std::ostream &operator<<(std::ostream &output, const ColorMatrix& m) {
		Value tmpValue;
		DefaultSerializer::serialize(m, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}

	void ColorMatrix::serialize(Value &node, bool setName) const {
		
		}


		bool ColorMatrix::deserialize(const Value &node) {

		
		}
}

