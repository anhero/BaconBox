#include "FlashMatrixComponent.h"
#include "BaconBox/Components/Transform.h"
#include "BaconBox/Console.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
namespace BaconBox {
	BB_ID_IMPL(FlashMatrixComponent);



	FlashMatrixComponent::FlashMatrixComponent(): MatrixComponent(), movieClipHolder(NULL){
	    initializeConnections();
	}

	void FlashMatrixComponent::setMatrix(const Matrix2D & m){
	    PRLN("STUB FlashMatrixComponent::setMatrix not implemented");
	}

	Matrix2D FlashMatrixComponent::getConcatMatrix(){
		AS3_DeclareVar(mc, *);
		AS3::local::var tempMC = movieClipHolder->getMovieClip();
		AS3_CopyVarxxToVar(mc, tempMC);
		inline_as3(
			    "import flash.geom.Transform;"
			    "import flash.geom.Matrix;"
			    "var matrix:Matrix = mc.transform.concatenatedMatrix\n"
			    "%0 = matrix.a\n"
			    "%1 = matrix.b\n"
			    "%2 = matrix.c\n"
			    "%3 = matrix.d\n"
			    "%4 = matrix.tx\n"
			    "%5 = matrix.ty\n"

		    : "=r"(concatMatrix.a), "=r"(concatMatrix.b), "=r"(concatMatrix.c), "=r"(concatMatrix.d), "=r"(concatMatrix.tx), "=r"(concatMatrix.ty)
			);
		return concatMatrix;
	}



	Matrix2D & FlashMatrixComponent::getMatrix(){
		AS3_DeclareVar(mc, *);
		AS3::local::var tempMC = movieClipHolder->getMovieClip();
		AS3_CopyVarxxToVar(mc, tempMC);
		inline_as3(
			    "import flash.geom.Transform;"
			    "import flash.geom.Matrix;"
			    "var matrix:Matrix = mc.transform.matrix\n"
			    "%0 = matrix.a\n"
			    "%1 = matrix.b\n"
			    "%2 = matrix.c\n"
			    "%3 = matrix.d\n"
			    "%4 = matrix.tx\n"
			    "%5 = matrix.ty\n"

		    : "=r"(matrix.a), "=r"(matrix.b), "=r"(matrix.c), "=r"(matrix.d), "=r"(matrix.tx), "=r"(matrix.ty)
			);
		return matrix;
	}


	void FlashMatrixComponent::initializeConnections() {
		// We add the connections.
		this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
		this->MatrixComponent::initializeConnections();
	}



}
