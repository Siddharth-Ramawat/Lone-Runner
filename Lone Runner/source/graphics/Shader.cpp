#include <Windows.h>
#include <GL\glew.h>

#include "graphics\Shader.h"
#include <glm\gtc\type_ptr.hpp> //for glm :: value_ptr()

Shader::Shader(std::string vertexFileName, std::string fragmentFileName)
{
	this->ready = false;
	this->vertexFilename = vertexFileName;
	this->fragmentFilename = fragmentFileName;
	if (this->Load() < 1)
	{
		std :: cout << "Error loading Shader Sources!" << std :: endl;
		return;

	}
	if (this->Compile() < 1)
	{
		std::cout << "Error compliling Shader Sources!" << std::endl;
		return;
	}
	if (this->Link() < 1)
	{
		std::cout << "Error linking Shader Sources!" << std::endl;
		return;
	}
	this->ready = true;
}

int Shader ::getAttribute(std ::string name)
{
	return glGetAttribLocation(this->shaderProgram, name.c_str());
}

GLint Shader::getUniformLocation(std::string name)
{
	return glGetUniformLocation(this->shaderProgram, name.c_str()); // openGL is designed for C so we use c_str()
}

void Shader::setUniformMatrix(GLint location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); //glUniform can take a variety of types -> 4fv means 4 float values
	/*void glUniformMatrix4fv(	GLint location,
 	GLsizei count,
 	GLboolean transpose,
 	const GLfloat *value);
 */
}

int Shader::Load()
{
	this->vertFile.open(this->vertexFilename,std ::ios::in);
	if (!vertFile)
	{
		return -1;
	}
	this->vertexSourceStream << vertFile.rdbuf();
	
	this->fragFile.open(this->fragmentFilename,std :: ios::in);
	if (!fragFile)
	{
		return -2;
	}
	this->fragmentSourceStream << fragFile.rdbuf();
	this->vertexSource = this->vertexSourceStream.str();

	this->fragmentSource = this->fragmentSourceStream.str();

	 
	return 1;
}

int Shader::Compile()
{
	const char* tempSource = this->vertexSource.c_str();
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &tempSource, 0);
	glCompileShader(this->vertexShader);
	GLint compiled;
	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == false)
	{
		unsigned int maxLength;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* vertexCompileLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(this->vertexShader, maxLength, (GLsizei*)&maxLength, vertexCompileLog);
		std :: cout << "Vertex shader error: " << std :: endl << vertexCompileLog << std::endl << std::endl;
		free(vertexCompileLog);
		return -1;
	}

	tempSource = this->fragmentSource.c_str();
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &tempSource, 0);
	glCompileShader(this->fragmentShader);
	glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &compiled);
	if (compiled == false)
	{
		unsigned int maxLength;
		glGetShaderiv(this->fragmentShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* fragmentCompileLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(this->fragmentShader, maxLength, (GLsizei*)&maxLength, fragmentCompileLog);
		std:: cout << "Fragment shader error: " << std::endl << fragmentCompileLog << std::endl << std::endl;
		free(fragmentCompileLog);
		return -2;
	}
	return 1;
}

int Shader::Link()
{
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragmentShader);
	glLinkProgram(this->shaderProgram);
	
	GLint linked;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &linked);
	if(linked == false)
	{
		unsigned int maxLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char *programLinkLog = (char*)malloc(maxLength * sizeof(char));
		glGetProgramInfoLog(this->shaderProgram, maxLength, (GLsizei*)&maxLength, programLinkLog);
		std::cout << "Program Link Error: " << std::endl << programLinkLog << std::endl << std::endl;
		free(programLinkLog);
		return -1;
	}

	return 1;

}

bool Shader::Use()
{
	if (this->ready)
	{
		glUseProgram(this->shaderProgram);
	}
	return this->ready;
}
Shader :: ~Shader()
{
	
}



/*uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;*/