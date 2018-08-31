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
using std::cerr;
using std::istreambuf_iterator;

enum ShaderType { VERTEX, FRAGMENT, GEOMETRY, TESSELLATION };

class ShaderPath {
private:
	string source;
	ShaderType type;

public:
	ShaderPath() {}
	ShaderPath(string source, ShaderType type);
	~ShaderPath();

	// Getters and setters
	string getSource();
	ShaderType getType();
	void setSource(string source);
	void setType(ShaderType type);
};