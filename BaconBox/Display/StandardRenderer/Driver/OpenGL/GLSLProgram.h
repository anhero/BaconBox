#ifndef BB_GLSLPROGRAM_H
#define BB_GLSLPROGRAM_H
#include "GLSLShader.h"
#include <map>
#include <vector>

//Inspired by the book More OpenGL game programming by Dave Astle
//http://glbook.gamedev.net/
#include "BaconBox/Display/StandardRenderer/Driver/OpenGL/BBOpenGL.h"
#include <string>
namespace BaconBox{
    class GLSLProgram
    {
    typedef std::map<std::string,int> uniformmap;
        public:
            GLSLProgram();
            GLSLProgram(const std::string &shaderSrc, unsigned int shaderType=GL_VERTEX_SHADER);
            GLSLProgram(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc);
            virtual ~GLSLProgram();

            void attach(GLSLShader &shader);
            void attach(GLSLShader *shader);

            void detach(GLSLShader &shader);
            void detach(GLSLShader *shader);
            void link();
            void use() const;
            void disable() const;

            	GLuint getHandle() const;
	void validate() const;
		void getParameter(GLenum param, GLint *data) const;
	bool IsValidProgram() const;



            void sendUniform(const std::string &name, float x);
            void sendUniform(const std::string &name, float x, float y);
            void sendUniform(const std::string &name, float x, float y, float z);
            void sendUniform(const std::string &name, float x, float y, float z, float w);
            void sendUniform(const std::string &name, int x);
            void sendUniform(const std::string &name, int x, int y);
            void sendUniform(const std::string &name, int x, int y, int z);
            void sendUniform(const std::string &name, int x, int y, int z, int w);
            void sendUniform(const std::string &name, float *m, bool transp=false, int size=4);

            void sendUniform(GLuint location, float x);
            void sendUniform(GLuint location, float x, float y);
            void sendUniform(GLuint location, float x, float y, float z);
            void sendUniform(GLuint location, float x, float y, float z, float w);
            void sendUniform(GLuint location, int x);
            void sendUniform(GLuint location, int x, int y);
            void sendUniform(GLuint location, int x, int y, int z);
            void sendUniform(GLuint location, int x, int y, int z, int w);
            void sendUniform(GLuint location, float *m, bool transp=false, int size=4);

            GLuint getUniformLocation(const std::string &name) const;
            void setAttributeLocation(const std::string &name, GLuint location);
            GLuint getAttributeLocation(const std::string &name) const;

            	void getProgramLog(std::string &log) const;



            	void getAttributeInfo(GLuint location, std::string &name, GLenum &type, GLint &size) const;
            void getUniformInfo(GLuint location, std::string &name, GLenum &datatype, GLint &size) const;

        private:
                int getLoc(const std::string &name);
              GLSLShader *vertexShader;
              GLSLShader *fragmentShader;
              GLint programHandle;
              uniformmap uniforms;

    };
}
#endif // BB_GLSLSHADER_H
