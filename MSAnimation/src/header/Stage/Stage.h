#pragma once

// Global includes
#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

// Local includes
#include <Core/CoreColleague.h>
#include <Core/Core.h>
#include <Model/Model.h>
#include <Model/Shader.h>
#include <Batch/Camera.h>

class Stage : public CoreColleague {
private:
	vector<Model*> models;
	Camera* camera;
	Shader* shader;
	mat4 projection;

	void render();

public:
	Stage(Core* mediator);
	~Stage();

	// Overrides
	void send(string message, void* data) override;
	void receive(string message, void* data) override;

	// Methods
	void setCamera(Camera* camera);
	void setShader(Shader* shader);
	void addModel(Model* model);
	void updateProjection(const int width, const int height);
};