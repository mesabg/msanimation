#include <Model/Model.h>

Model::Model()
{
	this->directory = "";
}

Model::~Model()
{
	// Do something
}

vector<Mesh> Model::getMeshes()
{
	return this->meshes;
}

string Model::getDirectory()
{
	return this->directory;
}

vector<Texture> Model::getTextures()
{
	return this->textures;
}

Texture Model::getTexture(int index)
{
	return this->textures[index];
}

void Model::setMeshes(vector<Mesh> meshes)
{
	this->meshes = meshes;
}

void Model::setDirectory(string directory)
{
	this->directory = directory;
}

void Model::setTextures(vector<Texture> textures)
{
	this->textures = textures;
}

void Model::addMesh(Mesh mesh)
{
	this->meshes.push_back(mesh);
}

void Model::addTexture(Texture texture)
{
	this->textures.push_back(texture);
}

void Model::clearMeshes()
{
	this->meshes.clear();
}

void Model::clearTextures()
{
	this->textures.clear();
}

void Model::render(Shader* shader)
{
	for (Mesh mesh : this->meshes){
		mesh.render(shader);
	}
}