#include "DefaultColorTransform.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Console.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
namespace BaconBox {


	DefaultColorTransform::DefaultColorTransform() : ColorTransform(), useCustomMatrix(false), entityContainer(NULL), invalidated(true), concatMatrix(), matrix(1,0,1,0,1,0,1,0){
	    initializeConnections();
	}


	void DefaultColorTransform::initializeConnections(){
	    this->addConnection(new ComponentConnection<EntityContainer>(&this->entityContainer));
	}


	void DefaultColorTransform::setFrameColorTransform(int frame){
	    matrix =  matrixByParentFrame[frame];
		invalidated = true;
	}
		void DefaultColorTransform::setColorMultiplier(float r, float g, float b, float a){
			matrix.colorMultiplier.setRGBA(r, g, b, a);
            useCustomMatrix = true;
		}

		void DefaultColorTransform::setColorOffset(float r, float g, float b, float a){
			matrix.colorOffset.setRGBA(r, g, b, a);
            useCustomMatrix = true;
		}

        void DefaultColorTransform::setAlphaMultiplier(float alpha){
			matrix.colorMultiplier.setAlpha(alpha);
            useCustomMatrix = true;
        }
	bool DefaultColorTransform::needConcat(){
		MovieClipEntity * parentMC = entityContainer->getParent();
		return (invalidated || reinterpret_cast<DefaultColorTransform*>(parentMC->getColorTransform())->needConcat());
	}
	

	ColorMatrix & DefaultColorTransform::getConcatColorMatrix(){
		MovieClipEntity * parentMC = entityContainer->getParent();
		if(!useCustomMatrix && entityContainer && parentMC){
			if(needConcat()){
				concatMatrix = matrix;
				concatMatrix.concat(parentMC->getConcatColorMatrix());
				return concatMatrix;
			}
			else{
				return concatMatrix;
			}
	    }
	    else{
	    	return matrix;
	    }
	}

}
