#pragma once

// Global includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

// using spaces
using glm::vec3;
using glm::vec2;

struct Vertex
{
	// Position
	vec3 position;
	// Normal
	vec3 normal;
	// TexCoords
	vec2 texCoords;
};