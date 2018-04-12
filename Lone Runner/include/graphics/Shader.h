#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <glm\glm.hpp>
#ifndef SHADER 
#define SHADER
class Shader
{
public:
	Shader(std ::string vertexFileName, std ::string fragmentFileName);
	bool Use();
	int getAttribute(std::string name);
	
	GLint getUniformLocation(std::string name);
	void setUniformMatrix(GLint location, glm::mat4 matrix );

	~Shader();
private:
	std::ifstream vertFile, fragFile;
	std::string vertexFilename, fragmentFilename;
	std::stringstream vertexSourceStream, fragmentSourceStream;
	std::string vertexSource, fragmentSource;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	bool ready;
	int Load();
	 int Compile();
	int Link();

};
#endif