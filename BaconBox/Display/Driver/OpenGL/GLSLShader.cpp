#include "GLSLShader.h"
#include "BaconBox/Console.h"
using namespace BaconBox;
GLSLShader::GLSLShader(unsigned int shaderType): compiled(false){
    shaderHandle = glCreateShader(shaderType);
}

GLSLShader::GLSLShader(const std::string &src, unsigned int shaderType): compiled(false){
        shaderHandle = glCreateShader(shaderType);
        setSource(src);
        compile();
}


GLSLShader::~GLSLShader(){
    glDeleteShader(shaderHandle);
}

GLuint GLSLShader::getHandle() const
{
	return shaderHandle;
}

void GLSLShader::getShaderLog(std::string &log) const{
	GLchar *debug;
	GLint debugLength;
	getParameter(GL_INFO_LOG_LENGTH, &debugLength);

	debug = new GLchar[debugLength];
	glGetShaderInfoLog(shaderHandle, debugLength, &debugLength, debug);

    //cout << debug;
	log.append(debug,0,debugLength);
    delete [] debug;
}

void GLSLShader::getParameter(GLenum param, GLint *data) const{
	glGetShaderiv(shaderHandle, param, data);
}



void GLSLShader::compile(){
 GLint compiled;
  glCompileShader(shaderHandle);
  glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
    this->compiled = (compiled);
    if(!compiled){
        std::string log;
        getShaderLog(log);
        Console__error(log);
    }
}

bool GLSLShader::isCompiled(){
    return compiled;
}

void GLSLShader::setSource(const std::string &src){
    const char *source = src.c_str();
	glShaderSource(shaderHandle,1,static_cast<const GLchar**>(&source),NULL);
}
