#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <iostream>
#include<string>
#include<fstream> // allows to read from files etc.
#include<sstream> // stringstream associates a string object with a stream allowing you to read from the string as if it were a stream
#include<cerrno> // This header is part of the error handling library. C errno, C as in C programming language


std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();

};

class shaderClass
{
};


#endif // !SHADER_CLASS_H