#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4146)

// Local includes
#include <Model/Mesh.h>
#include <Model/ComplexMesh.h>

class Model {
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures;
	ComplexMesh* complexMesh;

public:
	Model();
	~Model();

	// Getters and setters
	vector<Mesh> getMeshes();
	string getDirectory();
	vector<Texture> getTextures();
	Texture getTexture(int index);
	ComplexMesh* getComplexMesh();
	void setMeshes(vector<Mesh> meshes);
	void setComplexMesh(ComplexMesh* complexMesh);
	void setMesh(int index, Mesh mesh);
	void setDirectory(string directory);
	void setTextures(vector<Texture> textures);
	void addMesh(Mesh mesh);
	void addTexture(Texture texture);
	void clearMeshes();
	void clearTextures();


	// General functions
	void render(Shader* shader);
};
