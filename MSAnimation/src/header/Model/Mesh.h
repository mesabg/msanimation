#pragma once

// Global includes
#include <vector>

// Local includes
#include <Model/Vertex.h>
#include <Model/Texture.h>
#include <Model/Shader.h>

// Using spaces
using std::vector;

class Mesh {
private:

	// Mesh data
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	// Normalize data
	vec3 min;
	vec3 max;

	// Render Data
	GLuint VAO, VBO, EBO;

public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, vec3 min = vec3(0.0f, 0.0f, 0.0f), vec3 max = vec3(0.0f, 0.0f, 0.0f));
	~Mesh();

	// Getter and setters
	vector<Vertex> getVertices();
	vector<GLuint> getIndices();
	vector<Texture> getTextures();
	void setVertices(vector<Vertex> vertices);
	void setIndices(vector<GLuint> indices);
	void setTextures(vector<Texture> textures);

	// General functions
	void render(Shader* shader);
	void buildBuffers();
	void normalize();
};