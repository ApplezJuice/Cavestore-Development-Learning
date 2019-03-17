#include "headers/glslProgram.h"
#include "headers/errors.h"

#include <fstream>
#include <vector>

glslProgram::glslProgram() : 
	_numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{

}

glslProgram::~glslProgram()
{
	
}

void glslProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath)
{
	_programID = glCreateProgram();

	// creates shader objects from the vertex and fragment files
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
	{
		fatalError("Vertex shader failed to be created!");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
	{
		fatalError("Fragment shader failed to be created!");
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilepath, _fragmentShaderID);

}

void glslProgram::linkShaders()
{
	// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a program object.

	// Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// Link our program
	glLinkProgram(_programID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(_programID);
		// Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Shaders failed to link");
	}

	// Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void glslProgram::addAttribute(const std::string & attributeName)
{
	glBindAttribLocation(_programID, _numAttributes, attributeName.c_str());
	_numAttributes++;
}

GLint glslProgram::getUniformLocation(const std::string& uniformName)
{
	// returns a glint location from the program using the passed in uniformName
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	// returns this if the uniform we are asking for does not exist
	if (location == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + uniformName + " not found in shader.");
	}
	return location;
}

void glslProgram::use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
	{
		// will use 0 for vertexPosition in our .vert file as that is the only attrib
		glEnableVertexAttribArray(i);
	}
}

void glslProgram::unUse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void glslProgram::compileShader(const std::string & filePath, GLuint id)
{
	// opens the file
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		fatalError("Failed to open " + filePath);
	}

	// read file contents
	std::string fileContents = "";
	std::string line;

	// reads from vertexfile and puts into line and then adds it to filecontents
	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}

	vertexFile.close();

	// glShaderSource tells the openGL where to get the source
	// wants an array of c strings
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	// error checking to make sure it all worked correctly
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// the max length includes the null char aka a string basically
		// makes the size of the vector maxlength which gets from 'GL_INFO_LOG_LENGTH' - length of the log it creates
		// glGetShaderInfoLog puts the log it created and puts it into the vector errorLog
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		//provide the infolog
		glDeleteShader(id); // don't leak

		// errorLog is an array of characters which is basically a c str, this will print out our vector as a string
		std::printf("%s\n", &errorLog[0]);
		fatalError("Shader " + filePath + " failed to compile");
	}
}
