#pragma once

// Global includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glew/glew.h>
#include <assimp/Importer.hpp>

// Using spaces
using std::string;

class Texture {
private:
	GLuint id;
	string type;
	aiString path;

public:
	Texture();
	Texture(GLuint id, string type, aiString path) :id(id), type(type), path(path) {}
	~Texture();

	// Getters and setters
	GLuint getId();
	string getType();
	aiString getPath();
	void setId(GLuint id);
	void setType(string type);
	void setPath(aiString path);
};