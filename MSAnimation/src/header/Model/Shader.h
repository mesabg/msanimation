#pragma once

// Local includes
#include <Model/ShaderPath.h>

class Shader {
private:
	GLuint program;

public:

	Shader();
	~Shader();

	// Getters and setters
	GLuint getProgram();
	void setProgram(GLuint program);

	// General functions
	void load( vector< ShaderPath* >& paths );
	void use();
};