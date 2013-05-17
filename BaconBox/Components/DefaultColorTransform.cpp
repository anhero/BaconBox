#include "DefaultColorTransform.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/MovieClipEntity/MovieClipEntity.h"
namespace BaconBox {


	DefaultColorTransform::DefaultColorTransform() : ColorTransform(), color(Color::WHITE), entityContainer(NULL), concatMatrix(), matrix(1,0,1,0,1,0,1,0){
	    initializeConnections();
	}


	void DefaultColorTransform::initializeConnections(){
	    this->addConnection(new ComponentConnection<EntityContainer>(&this->entityContainer));
	}


	void DefaultColorTransform::setAlpha(uint8_t alpha){
		matrix.setAlphaMultiplier(static_cast<float>(alpha)/255.0f);
	}


	ColorMatrix & DefaultColorTransform::getConcatColorMatrix(){
		MovieClipEntity * parentMC = entityContainer->getParent();
		if(entityContainer && parentMC){
	    	concatMatrix = matrix;
			concatMatrix.concat(parentMC->getConcatColorMatrix());
			return concatMatrix;
	    }
	    else{
	    	return matrix;
	    }
	}


	Color & DefaultColorTransform::getConcatColor(){
	    color = getConcatColorMatrix().multiplyWithColor(Color::WHITE);
	    return color;
	}


}
