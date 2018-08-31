#pragma once

// Local includes
#include <Model/ShaderPath.h>

class Shader {
private:
	GLuint program;
	vector<GLuint> shaders;

	bool loadFile(string strFilename, GLuint iHandle);
	void checkLinkingErrors();

public:

	Shader();
	~Shader();

	// Getters and setters
	GLuint getProgram();
	void setProgram(GLuint program);

	// General functions
	void load(vector< ShaderPath* > paths);
	void load(ShaderPath* path);
	void create();
	void create_link();
	void link(vector<string> attributes, vector<string> uniforms);
	void enable();
	void disable();
};