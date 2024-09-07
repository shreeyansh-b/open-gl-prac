#include "Shader.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();


	/*
	Unique Identifier: The identifier (in this case, stored in vertexShader) is a unique integer
	that OpenGL uses internally to manage and access the shader object.
	It ensures that each shader object can be uniquely identified and manipulated.

	Not a Pointer: While it acts like a handle or reference,
	it doesn’t point to a memory location like a typical pointer.
	Instead, it's an opaque handle that OpenGL uses to track and manage resources.

	Usage: You use this identifier in subsequent OpenGL function calls
	(e.g., glShaderSource, glCompileShader, glAttachShader) to perform operations on the shader object.

	Here’s an analogy: Think of the unique identifier as a ticket number you get at a service center.
	It’s not a direct link to a specific employee (like a pointer to memory),
	but it uniquely identifies your request and allows you to interact with the system.
*/


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/*
		The glShaderSource function takes the shader object to compile to as its first argument.
		The second argument specifies how many strings we're passing as source code, which is only one.
		The third parameter is the actual source code of the vertex shader and we can leave the 4th parameter to NULL.
	*/
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);


	// shader program to use both these shaders
	// A shader program object is the final linked version of multiple shaders combined. 
	// To use the recently compiled shaders we have to link them to a shader program object 
	// and then activate this shader program when rendering objects.
	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate()
{
	// Every shader and rendering call after glUseProgram will now use this program object (and thus the shaders).
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}