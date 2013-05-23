#ifndef BB_GLSLSHADER_H
#define BB_GLSLSHADER_H
#include "BaconBox/Display/Driver/OpenGL/BBOpenGL.h"
#include <string>

//Inspired by the book More OpenGL game programming by Dave Astle
//http://glbook.gamedev.net/

namespace BaconBox{
    class GLSLShader
    {
        public:
            GLSLShader(const std::string &src, unsigned int shaderType);
            GLSLShader(unsigned int shaderType);
            virtual ~GLSLShader();

              void compile();
              GLuint getHandle() const;
          void getParameter(GLenum param, GLint *data) const;
          void getShaderLog(std::string &log) const;
            bool isCompiled();
            void setSource(const std::string &src);
        private:
              GLint shaderHandle;
              bool compiled;

    };
}
#endif // BB_GLSLSHADER_H
