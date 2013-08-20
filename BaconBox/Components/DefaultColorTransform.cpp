#include "DefaultColorTransform.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Console.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
namespace BaconBox {


	DefaultColorTransform::DefaultColorTransform() : ColorTransform(), useCustomMatrix(false), entityContainer(NULL), invalidated(true), concatMatrix(), matrixByParentFrame(NULL), matrix(1,0,1,0,1,0,1,0){
	    initializeConnections();
	}


	void DefaultColorTransform::initializeConnections(){
	    this->addConnection(new ComponentConnection<EntityContainer>(&this->entityContainer));
	}


	void DefaultColorTransform::setFrameColorTransform(int frame){
		if(!useCustomMatrix && matrixByParentFrame){
			if(matrix.colorOffset !=  (*matrixByParentFrame)[frame].colorOffset || matrix.colorMultiplier !=  (*matrixByParentFrame)[frame].colorMultiplier) {
				matrix =  (*matrixByParentFrame)[frame];
				invalidated = true;
			}

		}
			
	}
		void DefaultColorTransform::setColorMultiplier(float r, float g, float b, float a){
			matrix.colorMultiplier.setRGBA(r, g, b, a);
            useCustomMatrix = true;
			invalidated = true;
		}

		void DefaultColorTransform::setColorOffset(float r, float g, float b, float a){
			matrix.colorOffset.setRGBA(r, g, b, a);
            useCustomMatrix = true;
			invalidated = true;
		}

        void DefaultColorTransform::setAlphaMultiplier(float alpha){
			matrix.colorMultiplier.setAlpha(alpha);
            useCustomMatrix = true;
			invalidated = true;
        }
	bool DefaultColorTransform::needConcat(){
		MovieClipEntity * parentMC = entityContainer->getParent();
		return (invalidated || (parentMC && reinterpret_cast<DefaultColorTransform*>(parentMC->getColorTransform())->needConcat()));
	}
	
	ColorMatrix &DefaultColorTransform::getMatrix(){
		return matrix;
	}
	

	ColorMatrix & DefaultColorTransform::getConcatColorMatrix(){
		MovieClipEntity * parentMC = entityContainer->getParent();
		if( entityContainer && parentMC){
			if(needConcat()){
				concatMatrix = matrix;
				concatMatrix.concat(parentMC->getConcatColorMatrix());
				
				//TODO: the invalidated system does not work, we need to think of something else to prevent over concatenetion of matrix, a version system where we increment an int maybe?
//				invalidated = false;

				return concatMatrix;
			}
			else{
				return concatMatrix;
			}
	    }
	    else{
			invalidated = false;
	    	return matrix;
	    }
	}

}
