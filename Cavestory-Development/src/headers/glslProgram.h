#pragma once

#include <string>
#include <glew.h>

class glslProgram
{
public:
	glslProgram();
	~glslProgram();

	// will read our vertex / frag shader from file then compile them into a format that OpenGL can use
	// uses a constant because we are not going to change the original file path
	// passing in a reference so it will save resources
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);

	// will link our shaders together in the final program
	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLint getUniformLocation(const std::string& uniformName);

	void use();
	void unUse();

private:

	int _numAttributes;

	void compileShader(const std::string& filePath, GLuint id);

	// need an ID to hold onto our shader program and individual shaders
	// the ID that will refer to the final program
	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};