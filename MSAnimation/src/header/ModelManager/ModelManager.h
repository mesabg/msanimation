#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4146)

// Global includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL2/SOIL2.h>

// Local includes
#include <Core/CoreColleague.h>
#include <Core/Core.h>
#include <Model/Model.h>
#include <igl/readOBJ.h>

// Using spaces
using std::cout;
using std::endl;
using Eigen::MatrixXd;
using Eigen::MatrixXi;

class ModelManager : public CoreColleague
{
private:
	// Variables
	static ModelManager* uniqueModelManager;

	// Initializers
	ModelManager(Core* mediator);
	~ModelManager();

	// General functions
	Model* load(string filePath);
	void processNode(Model* model, aiNode* node, const aiScene* scene);
	Mesh processMesh(Model * model, aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(Model * model, aiMaterial *mat, aiTextureType type, string typeName);
	GLuint mergeComponent(vector<vec3> &components, vec3 &position);

public:
	// Get Instance
	static ModelManager* instance(Core* mediator);
	static void destroy();

	// Override
	void send(string message, void* data) override;
	void receive(string message, void* data) override;
};

GLint TextureFromFile(const char *path, string directory);