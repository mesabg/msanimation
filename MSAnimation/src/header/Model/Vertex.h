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

class Vertex {
public:
	vec3 position;
	vec3 normal;
	vec2 texCoords;

	Vertex();
	Vertex(vec3 position, vec3 normal, vec2 texCoords) :position(position), normal(normal), texCoords(texCoords) {}
	~Vertex();

	// Getters and setters
	vec3 getPosition();
	vec3 getNormal();
	vec2 getTexCoords();
	void setPosition(vec3 position);
	void setNormal(vec3 normal);
	void setTexCoords(vec2 texCoords);
};