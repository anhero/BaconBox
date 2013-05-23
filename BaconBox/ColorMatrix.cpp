#include "ColorMatrix.h"

#include "BaconBox/Helper/Serialization/Array.h"
#include "BaconBox/Helper/Serialization/Object.h"

#include "BaconBox/Helper/Serialization/Value.h"
#include "BaconBox/Helper/Serialization/DefaultSerializer.h"
#include "BaconBox/Helper/Serialization/Serializer.h"

#include "BaconBox/Helper/MathHelper.h"
namespace BaconBox {

	ColorMatrix::ColorMatrix():matrix(20, 0){
        matrix[0] = 1;
        matrix[6] = 1;
        matrix[12] = 1;
        matrix[18] = 1;
	}

	ColorMatrix::ColorMatrix(float redMultiplier, float redOffset, float greenMultiplier, float greenOffset,
                float blueMultiplier, float blueOffset, float alphaMultiplier, float alphaOffset):matrix(20, 0){
                matrix[0] = redMultiplier;
                matrix[4] = redOffset;

                matrix[6] = greenMultiplier;
                matrix[9] = greenOffset;

                matrix[12] = blueMultiplier;
                matrix[14] = blueOffset;

                matrix[18] = alphaMultiplier;
                matrix[19] = alphaOffset;
    }

    ColorMatrix::ColorMatrix(const ColorMatrix &src):matrix(20){
        for(int i = 0; i < matrix.size() ; i++){
            matrix[i] = src.matrix[i];
	    }
	}

	ColorMatrix &ColorMatrix::operator=(const ColorMatrix &src) {
	    for(int i = 0; i < matrix.size() ; i++){
            matrix[i] = src.matrix[i];
	    }
		return *this;
	}


	ColorMatrix ColorMatrix::operator*(const ColorMatrix & m) const{
	    ColorMatrix temp;

	    //longer but complete method
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


        //faster and minimal method
        temp.matrix[0] = MathHelper::clamp((matrix[0] * m.matrix[0]), -1.0f, 1.0f);
	    temp.matrix[6] = MathHelper::clamp((matrix[6] * m.matrix[6]), -1.0f, 1.0f);
	    temp.matrix[12] = MathHelper::clamp((matrix[12] * m.matrix[12]), -1.0f, 1.0f);
	    temp.matrix[18] = MathHelper::clamp((matrix[18] * m.matrix[18]), -1.0f, 1.0f);

	    temp.matrix[4] = MathHelper::clamp((matrix[4] * m.matrix[0]) + m.matrix[4], -1.0f, 1.0f);
	    temp.matrix[9] = MathHelper::clamp((matrix[9] * m.matrix[6]) + m.matrix[9], -1.0f, 1.0f);
	    temp.matrix[14] = MathHelper::clamp((matrix[14] * m.matrix[12]) + m.matrix[14], -1.0f, 1.0f);
	    temp.matrix[19] = MathHelper::clamp((matrix[19] * m.matrix[18]) + m.matrix[19], -1.0f, 1.0f);

	    return temp;
	}



	ColorMatrix &ColorMatrix::operator*=(const ColorMatrix& m) {
		(*this) = (*this) * m;
		return (*this);
	}

	ColorMatrix & ColorMatrix::concat(const ColorMatrix & parent){
	    (*this) = parent * (*this);
	    return (*this);
	}

//	bool Matrix::isSkewed() const{
//	    return !(-b == c);
//	}
	void ColorMatrix::setAlphaMultiplier(float alpha){
        matrix[18] = alpha;
	}


    Color ColorMatrix::multiplyWithColor(const Color & c) const{
	    return Color(
                  (matrix[0] * c.getRed()) +  (matrix[1] * c.getGreen()) + (matrix[2] * c.getBlue()) + (matrix[3] * c.getAlpha()) + (matrix[4]),
                  (matrix[5] * c.getRed()) +  (matrix[6] * c.getGreen()) + (matrix[7] * c.getBlue()) + (matrix[8] * c.getAlpha()) + (matrix[9]),
                  (matrix[10] * c.getRed()) +  (matrix[11] * c.getGreen()) + (matrix[12] * c.getBlue()) + (matrix[13] * c.getAlpha()) + (matrix[14]),
                  (matrix[15] * c.getRed()) +  (matrix[16] * c.getGreen()) + (matrix[17] * c.getBlue()) + (matrix[18] * c.getAlpha()) + (matrix[19])
                  );
	}


	std::ostream &operator<<(std::ostream &output, const ColorMatrix& m) {
		Value tmpValue;
		DefaultSerializer::serialize(m, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}

	void ColorMatrix::serialize(Value &node, bool setName) const {
			if (setName) {
				node.setName("ColorMatrix");
			}

			Array array ;

			for(std::vector<float>::const_iterator i = matrix.begin(); i != matrix.end(); i++){
                array.push_back(*i);
			}

			node.setArray(array);
		}


		bool ColorMatrix::deserialize(const Value &node) {

			bool result = true;


		    Array array = node.getArray();
			if (array.size() == 20) {
                int index = 0;
                for(Array::iterator i = array.begin(); i != array.end(); i++){
                    matrix[index] = i->getDouble();
                    index++;
                }
			}
            else {
                result = false;
            }
                return result;
            }
		}


