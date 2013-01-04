/**
 * @file
 */
#ifndef BB_OPENGLMESHRENDERER_H
#define BB_OPENGLMESHRENDERER_H


#include "../../Core/Component.h"
namespace BaconBox {
	/**
	 * 
	 */
	class OpenGLMeshRenderer : public Component{
    public:
		OpenGLMeshRenderer();
        void render();
    private:
        
	};
}

#endif // BB_OPENGLMESHRENDERER_H