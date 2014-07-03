#include "FlashColorTransform.h"
#include "BaconBox/Console.h"
#include "BaconBox/Components/ComponentConnection.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>
namespace BaconBox {


	FlashColorTransform::FlashColorTransform() : ColorTransform(), matrix(){
	    initializeConnections();
	}

	void FlashColorTransform::initializeConnections(){
	    this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
	}


	ColorMatrix & FlashColorTransform::getMatrix(){
		AS3_DeclareVar(mc, *);
		AS3::local::var tempMC = movieClipHolder->getMovieClip();
		AS3_CopyVarxxToVar(mc, tempMC);
		float * cm = matrix.colorMultiplier.getComponents();
		float * co = matrix.colorOffset.getComponents();


		inline_as3(
			"import flash.geom.ColorTransform;"
			"var ct:ColorTransform = mc.transform.colorTransform\n"
			"%0 = ct.redMultiplier;\n" 
			"%1 = ct.greenMultiplier;\n" 
			"%2 = ct.blueMultiplier;\n" 
			"%3 = ct.alphaMultiplier;\n" 
			"%4 = ct.redOffset;\n" 
			"%5 = ct.greenOffset;\n" 
			"%6 = ct.blueOffset;\n" 
			"%7 = ct.alphaOffset;\n" 
			: "=r"(cm[0]), "=r"(cm[1]), "=r"(cm[2]), "=r"(cm[3]), 
			"=r"(co[0]), "=r"(co[1]), "=r"(co[2]), "=r"(co[3])
		);

	}

	ColorMatrix & FlashColorTransform::getConcatColorMatrix(){
		AS3_DeclareVar(mc, *);
		AS3::local::var tempMC = movieClipHolder->getMovieClip();
		AS3_CopyVarxxToVar(mc, tempMC);
		float * cm = matrix.colorMultiplier.getComponents();
		float * co = matrix.colorOffset.getComponents();


		inline_as3(
			"import flash.geom.ColorTransform;"
			"var ct:ColorTransform = mc.transform.concatenatedColorTransform\n"
			"%0 = ct.redMultiplier;\n" 
			"%1 = ct.greenMultiplier;\n" 
			"%2 = ct.blueMultiplier;\n" 
			"%3 = ct.alphaMultiplier;\n" 
			"%4 = ct.redOffset;\n" 
			"%5 = ct.greenOffset;\n" 
			"%6 = ct.blueOffset;\n" 
			"%7 = ct.alphaOffset;\n" 
			: "=r"(cm[0]), "=r"(cm[1]), "=r"(cm[2]), "=r"(cm[3]), 
			"=r"(co[0]), "=r"(co[1]), "=r"(co[2]), "=r"(co[3])
		);

	}

	void FlashColorTransform::setAlphaMultiplier(float alpha){
		AS3_DeclareVar(mc, *);
		AS3::local::var tempMC = movieClipHolder->getMovieClip();
		AS3_CopyVarxxToVar(mc, tempMC);

		inline_as3(
			"import flash.geom.ColorTransform;"
			"var ct:ColorTransform = new ColorTransform()\n"
			"ct.alphaMultiplier = %0;\n" 
			"mc.transform.colorTransform = ct;\n"
			: :"r"(alpha)
		);
	}

	void FlashColorTransform::setColorMultiplier(float r, float g, float b, float a){
		AS3_DeclareVar(mc, *);
		AS3::local::var tempMC = movieClipHolder->getMovieClip();
		AS3_CopyVarxxToVar(mc, tempMC);

		inline_as3(
			"import flash.geom.ColorTransform;"
			"var ct:ColorTransform = new ColorTransform()\n"
			"ct.redMultiplier = %0;\n" 
			"ct.greenMultiplier = %1;\n" 
			"ct.blueMultiplier = %2;\n" 
			"ct.alphaMultiplier = %3;\n" 
			"mc.transform.colorTransform = ct;\n"
			: :"r"(r),"r"(g),"r"(b),"r"(a)
		);
	}

	void FlashColorTransform::setColorOffset(float r, float g, float b, float a){
		AS3_DeclareVar(mc, *);
		AS3::local::var tempMC = movieClipHolder->getMovieClip();
		AS3_CopyVarxxToVar(mc, tempMC);

		inline_as3(
			"import flash.geom.ColorTransform;"
			"var ct:ColorTransform = new ColorTransform()\n"
			"ct.redOffset = %0*255;\n" 
			"ct.greenOffset = %1*255;\n" 
			"ct.blueOffset = %2*255;\n" 
			"ct.alphaOffset = %3*255;\n" 
			"mc.transform.colorTransform = ct;\n"
			: :"r"(r),"r"(g),"r"(b),"r"(a)
		);
	}

}
