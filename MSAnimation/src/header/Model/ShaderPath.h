#pragma once

// Global includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <glew\glew.h>

// Using spaces
using std::vector;
using std::map;
using std::string;
using std::ifstream;
using std::stringstream;
using std::cout;
using std::endl;

enum ShaderType { VERTEX, FRAGMENT, GEOMETRY, TESSELLATION };

class ShaderPath {
private:
	GLchar* source;
	ShaderType type;

public:
	ShaderPath() {}
	ShaderPath(GLchar* source, ShaderType type) :source(source), type(type) {}
	~ShaderPath();

	// Getters and setters
	GLchar* getSource();
	ShaderType getType();
	void setSource(GLchar* source);
	void setType(ShaderType type);
};