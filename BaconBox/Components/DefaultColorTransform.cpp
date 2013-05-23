#include "DefaultColorTransform.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Console.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
namespace BaconBox {


	DefaultColorTransform::DefaultColorTransform() : ColorTransform(), useCustomMatrix(false), entityContainer(NULL), concatMatrix(), matrix(1,0,1,0,1,0,1,0){
	    initializeConnections();
	}


	void DefaultColorTransform::initializeConnections(){
	    this->addConnection(new ComponentConnection<EntityContainer>(&this->entityContainer));
	}


	void DefaultColorTransform::setFrameColorTransform(int frame){
	    matrix =  matrixByParentFrame[frame];
	}
		void DefaultColorTransform::setColorMultiplier(float r, float g, float b, float a){
		    matrix.matrix[0] = r;
		    matrix.matrix[6] = g;
		    matrix.matrix[12] = b;
            matrix.matrix[18] = a;
            useCustomMatrix = true;
		}

		void DefaultColorTransform::setColorOffset(float r, float g, float b, float a){
		    matrix.matrix[4] = r;
		    matrix.matrix[9] = g;
		    matrix.matrix[14] = b;
            matrix.matrix[19] = a;
            useCustomMatrix = true;
		}

        void DefaultColorTransform::setAlphaMultiplier(float alpha){
            matrix.matrix[18] = alpha;
            useCustomMatrix = true;
        }

	ColorMatrix & DefaultColorTransform::getConcatColorMatrix(){
		MovieClipEntity * parentMC = entityContainer->getParent();
		if(!useCustomMatrix && entityContainer && parentMC){
	    	concatMatrix = matrix;
			concatMatrix.concat(parentMC->getConcatColorMatrix());
			return concatMatrix;
	    }
	    else{
	    	return matrix;
	    }
	}

}
