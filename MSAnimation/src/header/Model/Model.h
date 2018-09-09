#pragma once

// Local includes
#include <Model/Mesh.h>

class Model {
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures;

public:
	Model();
	~Model();

	// Getters and setters
	vector<Mesh> getMeshes();
	string getDirectory();
	vector<Texture> getTextures();
	Texture getTexture(int index);
	void setMeshes(vector<Mesh> meshes);
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
