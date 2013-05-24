#include "GLSLProgram.h"
#include "BaconBox/Console.h"

using namespace BaconBox;
GLSLProgram::GLSLProgram():fragmentShader(NULL), vertexShader(NULL){
    programHandle = glCreateProgram();
}

GLSLProgram::GLSLProgram(const std::string &shaderSrc, unsigned int shaderType):fragmentShader(NULL), vertexShader(NULL){
    programHandle = glCreateProgram();

    if(shaderType == GL_VERTEX_SHADER){
        vertexShader = new GLSLShader(shaderSrc, shaderType);
          attach(vertexShader);
    }
    else if(shaderType == GL_FRAGMENT_SHADER){
        fragmentShader = new GLSLShader(shaderSrc, shaderType);
        attach(fragmentShader);
    }
    link();

}
GLSLProgram::GLSLProgram(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc):fragmentShader(NULL), vertexShader(NULL){
    programHandle = glCreateProgram();
    vertexShader = new GLSLShader(vertexShaderSrc, GL_VERTEX_SHADER);
    attach(vertexShader);

    fragmentShader = new GLSLShader(fragmentShaderSrc, GL_FRAGMENT_SHADER);
    attach(fragmentShader);
    link();
}
GLSLProgram::~GLSLProgram(){

	if(vertexShader){
	    delete vertexShader;
	}
	if(fragmentShader){
		delete fragmentShader;
	}
	glDeleteProgram(programHandle);
}


void GLSLProgram::link(){
    glLinkProgram(programHandle);
	uniforms.clear();
}

void GLSLProgram::use() const{
	glUseProgram(programHandle);
}

void GLSLProgram::disable() const{
	glUseProgram(0);
}

void GLSLProgram::detach(GLSLShader &shader){
	glDetachShader(programHandle,shader.getHandle());
}

GLuint GLSLProgram::getHandle() const{
	return programHandle;
}


void GLSLProgram::attach(GLSLShader &shader){
	glAttachShader(programHandle, shader.getHandle());
}

void GLSLProgram::detach(GLSLShader *shader){
	detach(*shader);
}

void GLSLProgram::attach(GLSLShader *shader){
	attach(*shader);
}

bool GLSLProgram::IsValidProgram() const{
	GLint status;
	getParameter(GL_VALIDATE_STATUS,&status);
    return status;
}

void GLSLProgram::validate() const{
	glValidateProgram(programHandle);
}

void GLSLProgram::getParameter(GLenum param, GLint *data) const{
	glGetProgramiv(programHandle, param, data);
}

void GLSLProgram::sendUniform(const std::string &name, float x){
	glUniform1f(getLoc(name), x);
}

void GLSLProgram::sendUniform(const std::string &name, float x, float y){
	glUniform2f(getLoc(name), x, y);
}

void GLSLProgram::sendUniform(const std::string &name, float x, float y, float z){
	glUniform3f(getLoc(name), x, y, z);
}

void GLSLProgram::sendUniform(const std::string &name, float x, float y, float z,
			      float w){
	glUniform4f(getLoc(name), x, y, z, w);
}

void GLSLProgram::sendUniform(const std::string &name, int x){
	glUniform1i(getLoc(name), x);
}

void GLSLProgram::sendUniform(const std::string &name, int x, int y){
	glUniform2i(getLoc(name), x, y);
}

void GLSLProgram::sendUniform(const std::string &name, int x, int y, int z){
	glUniform3i(getLoc(name), x, y, z);
}

void GLSLProgram::sendUniform(const std::string &name, int x, int y, int z, int w){
	glUniform4i(getLoc(name), x, y, z, w);
}

void GLSLProgram::sendUniform(const std::string &name, float *matrix, bool transpose, int size){
	int loc = getLoc(name);

	switch(size)
    {
    case '2':
		glUniformMatrix2fv(loc, 0, transpose, matrix);
		break;
    case '3':
		glUniformMatrix3fv(loc, 0, transpose, matrix);
		break;
    case '4':
		glUniformMatrix4fv(loc, 0, transpose, matrix);
		break;
    }
}

// sendUniform functions with supplied location
void GLSLProgram::sendUniform(GLuint location, float x){
	glUniform1f(location, x);
}

void GLSLProgram::sendUniform(GLuint location, float x, float y){
	glUniform2f(location, x, y);
}

void GLSLProgram::sendUniform(GLuint location, float x, float y, float z){
	glUniform3f(location, x, y, z);
}

void GLSLProgram::sendUniform(GLuint location, float x, float y, float z, float w){
	glUniform4f(location, x, y, z, w);
}

void GLSLProgram::sendUniform(GLuint location, int x){
	glUniform1i(location, x);
}

void GLSLProgram::sendUniform(GLuint location, int x, int y){
	glUniform2i(location, x, y);
}

void GLSLProgram::sendUniform(GLuint location, int x, int y, int z){
	glUniform3i(location, x, y, z);
}

void GLSLProgram::sendUniform(GLuint location, int x, int y, int z,int w){
	glUniform4i(location, x, y, z, w);
}

void GLSLProgram::sendUniform(GLuint location, float *matrix, bool transpose, int size){
	switch(size)
	{
	case '2':
		glUniformMatrix2fv(location, 0, transpose, matrix);
		break;
	case '3':
		glUniformMatrix3fv(location, 0, transpose, matrix);
		break;
	case '4':
		glUniformMatrix4fv(location, 0, transpose, matrix);
		break;
	}
}

GLuint GLSLProgram::getUniformLocation(const std::string &name) const{
	return glGetUniformLocation(programHandle,name.c_str());
}

void GLSLProgram::setAttributeLocation(const std::string &name, GLuint location){
	glBindAttribLocation(programHandle,location, name.c_str());
}

GLuint GLSLProgram::getAttributeLocation(const std::string &name) const{
	return glGetAttribLocation(programHandle,name.c_str());
}

void GLSLProgram::getAttributeInfo(GLuint location, std::string &name, GLenum &datatype, GLint &size) const{
	// first we need to query the length of the longest name
	GLsizei length;
	getParameter(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,(GLint*)&length);

	std::vector<char> nametmp(length);
	GLsizei copiedsize;
	glGetActiveAttrib(programHandle,location,length,&copiedsize,&size,&datatype,&nametmp[0]);

	if(0 == copiedsize)
		return;

	name.assign(&nametmp[0]);
}

void GLSLProgram::getUniformInfo(GLuint location, std::string &name, GLenum &datatype, GLint &size) const{
	// first we need to query the length of the longest name
	GLint length;
	getParameter(GL_ACTIVE_UNIFORM_MAX_LENGTH,&length);

	std::vector<char> nametmp(length);
	GLsizei copiedsize;
	glGetActiveUniform(programHandle,location,length,&copiedsize,&size,&datatype,&nametmp[0]);

	if(0 == copiedsize)
		return;

	name.assign(&nametmp[0]);
}


void GLSLProgram::getProgramLog(std::string &log) const
{
	GLchar *debug;
	GLint debugLength;
	getParameter(GL_INFO_LOG_LENGTH, &debugLength);

	debug = new GLchar[debugLength];
	glGetProgramInfoLog(programHandle, debugLength, &debugLength, debug);

	//cout << debug;
	log.append(debug,0,debugLength);
	delete [] debug;
}


int GLSLProgram::getLoc(const std::string &name){
	int loc = -1;
	uniformmap::const_iterator it = uniforms.find(name);
	if(it == uniforms.end())
	{
		loc = glGetUniformLocation(programHandle, name.c_str());
		if(loc == -1)
		{
			std::string s;
			getProgramLog(s);
			s.append(name);
			s.append(" - is not a valid uniform variable name");
			Console__error(s);
		}
		uniforms.insert(uniformmap::value_type(name,loc));
	}
	else
		loc = it->second;

	return loc;
}
