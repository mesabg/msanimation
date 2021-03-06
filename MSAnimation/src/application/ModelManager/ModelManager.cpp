#include <ModelManager/ModelManager.h>

// General main initializations
ModelManager* ModelManager::uniqueModelManager = NULL;

ModelManager::ModelManager(Core* mediator) : CoreColleague(mediator)
{
	// Do something
}

ModelManager::~ModelManager()
{
	// Do something
}

Model * ModelManager::load(string filePath)
{
	// Create model object
	Model* model = new Model();

	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return NULL;
	}
	// Retrieve the directory path of the filepath
	model->setDirectory( filePath.substr(0, filePath.find_last_of("/\\")) );

	// Process ASSIMP's root node recursively
	this->processNode(model, scene->mRootNode, scene);

	// Normalize meshes
	int meshIndex = 0;
	for (Mesh mesh : model->getMeshes()) {
		mesh.normalize();
		model->setMesh(meshIndex, mesh);
	}

	return model;
}

void ModelManager::processNode(Model * model, aiNode * node, const aiScene * scene)
{
	// Process each mesh located at the current node
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene.
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		model->addMesh(this->processMesh(model, mesh, scene));
	}

	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(model, node->mChildren[i], scene);
	}
}

Mesh ModelManager::processMesh(Model * model, aiMesh * mesh, const aiScene * scene)
{
	// Data to fill
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	// Graph data
	vector<vec3> components;
	vector<TripletBoolean> adjacency;

	// Max/Min positions
	vec3 min = vec3(0.0f, 0.0f, 0.0f);
	vec3 max = vec3(0.0f, 0.0f, 0.0f);

	// Walk through each of the mesh's vertices
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		if (i == 0) {
			min.x = max.x = mesh->mVertices[i].x;
			min.y = max.y = mesh->mVertices[i].y;
			min.z = max.z = mesh->mVertices[i].z;
		} else {
			// -- Min
			min.x = mesh->mVertices[i].x < min.x ? mesh->mVertices[i].x : min.x;
			min.y = mesh->mVertices[i].y < min.y ? mesh->mVertices[i].y : min.y;
			min.z = mesh->mVertices[i].z < min.z ? mesh->mVertices[i].z : min.z;

			// -- Max
			max.x = mesh->mVertices[i].x > max.x ? mesh->mVertices[i].x : max.x;
			max.y = mesh->mVertices[i].y > max.y ? mesh->mVertices[i].y : max.y;
			max.z = mesh->mVertices[i].z > max.z ? mesh->mVertices[i].z : max.z;
		}

		Vertex vertex;
		glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

		// Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;
		this->mergeComponent(components, vector);

		// Normals
		if (mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		} else {
			vertex.normal = glm::vec3(0.0f);
		}

		// Texture Coordinates
		if (mesh->HasTextureCoords(0)) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else
		{
			vertex.texCoords = glm::vec2(0.0f);
		}

		//-- Tangents (Bi-Tangents will be calculated in the vertex shader)
		/*if (mesh->HasTangentsAndBitangents()) {
			this->glVBO.push_back(mesh->mTangents[j].x);
			this->glVBO.push_back(mesh->mTangents[j].y);
			this->glVBO.push_back(mesh->mTangents[j].z);
		}*/

		vertices.push_back(vertex);
	}

	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		// Retrieve all indices of the face and store them in the indices vector
		// Triangulate
		GLuint indexA = face.mIndices[0];
		GLuint indexB = face.mIndices[1];
		GLuint indexC = face.mIndices[2];

		indices.push_back(indexA);
		indices.push_back(indexB);
		indices.push_back(indexC);

		indexA = this->mergeComponent(components, vertices[indexA].position);
		indexB = this->mergeComponent(components, vertices[indexB].position);
		indexC = this->mergeComponent(components, vertices[indexC].position);

		adjacency.push_back(TripletBoolean(indexA, indexB, true));
		adjacency.push_back(TripletBoolean(indexB, indexA, true));
		adjacency.push_back(TripletBoolean(indexA, indexC, true));
		adjacency.push_back(TripletBoolean(indexC, indexA, true));
		adjacency.push_back(TripletBoolean(indexB, indexC, true));
		adjacency.push_back(TripletBoolean(indexC, indexB, true));

		/*for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			
			// Build adjacency
			for (GLuint k=j+1; k < face.mNumIndices; k++)
			{
				GLuint indexA = this->mergeComponent(components, vertices[face.mIndices[j]].position);
				GLuint indexB = this->mergeComponent(components, vertices[face.mIndices[k]].position);
				cout << "Indexes :: (" << indexA << ", " << indexB << ")\n";
				adjacency.push_back( TripletBoolean(indexA, indexB, true) );
				//adjacency.push_back( TripletBoolean(indexB, indexA, true) );
			}
		}*/
	}

	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		vector<Texture> diffuseMaps = this->loadMaterialTextures(model, material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// 2. Specular maps
		vector<Texture> specularMaps = this->loadMaterialTextures(model, material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	// Return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures, components, adjacency, min, max);
}

vector<Texture> ModelManager::loadMaterialTextures(Model * model, aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		GLboolean skip = false;

		for (GLuint j = 0; j < model->getTextures().size(); j++)
		{
			if (model->getTexture(j).path == str)
			{
				textures.push_back(model->getTexture(j));
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}

		if (!skip)
		{   // If texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), model->getDirectory());
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);

			model->addTexture(texture); // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}

	return textures;
}

GLuint ModelManager::mergeComponent(vector<vec3>& components, vec3 & position)
{
	GLuint index = 0;
	for (vec3 component : components) {
		if (component == position)
			return index;
		index++;
	}
	components.push_back(position);
	return index;
}

ModelManager * ModelManager::instance(Core * mediator)
{
	if (!uniqueModelManager)
		uniqueModelManager = new ModelManager(mediator);
	return uniqueModelManager;
}

void ModelManager::destroy()
{
	if (!uniqueModelManager) return;
	uniqueModelManager->~ModelManager();
}

void ModelManager::send(string message, void * data)
{
	this->mediator->send(message, data, this);
}

void ModelManager::receive(string message, void * data)
{
	if (message == "FileManager::fileReaded") {
		string filePath((char*)data);
		// Proccess the data
		Model* model = this->load(filePath);
		this->send("ModelManager::modelLoaded", (void*)model);
	}
}

GLint TextureFromFile(const char * path, string directory)
{
	//Generate texture ID and load texture data
	string filename = string(path);
	filename = directory + "\\" + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;

	unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	string response = image == NULL ? "IMAGE DOES NOT EXIST" : "IMAGE IS LOADED";

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return textureID;
}
