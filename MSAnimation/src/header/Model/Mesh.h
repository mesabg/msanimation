#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4146)

// Global includes
#include <vector>
#include <assimp/scene.h>
#include <Eigen/Sparse>
#include <glm/gtc/reciprocal.hpp>

// Local includes
#include <Model/Vertex.h>
#include <Model/Texture.h>
#include <Model/Shader.h>

// Using spaces
using std::vector;
using std::pair;
using glm::length;
using Eigen::SparseMatrix;
using Eigen::Triplet;
using Eigen::MatrixXd;

class Mesh {
private:

	// Mesh data
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	// Mesh scene
	aiMesh *mesh;

	// Graph representation data
	SparseMatrix<bool> *adjacent;
	SparseMatrix<GLfloat> *laplacian;

	// Normalize data
	vec3 min;
	vec3 max;

	// Render Data
	GLuint VAO, VBO, EBO;

	// Private functions
	pair<GLuint, GLuint> oppositeVerticesToEdge(GLuint i, GLuint j);

public:
	Mesh(aiMesh *mesh, vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, vec3 min = vec3(0.0f, 0.0f, 0.0f), vec3 max = vec3(0.0f, 0.0f, 0.0f));
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
	SparseMatrix<bool>* calculateAdjacentMatrix();
	SparseMatrix<float>* calculateLaplacianMatrix();
};