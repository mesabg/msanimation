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

struct Texture
{
	GLuint id;
	string type;
	aiString path;
};