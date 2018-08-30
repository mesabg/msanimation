#pragma once

// Global includes
#include <string>
#include <iostream>
#include <vector>


// Local includes
#include <Core/CoreColleague.h>
#include <Core/Core.h>
#include <Model/Model.h>
#include <Batch/Camera.h>

class Stage : public CoreColleague {
private:
	vector<Model*> models;
	Camera* camera;

	void render();

public:
	Stage(Core* mediator);
	~Stage();

	// Overrides
	void send(string message, void* data) override;
	void receive(string message, void* data) override;

	// Methods
	void setCamera(Camera* camera);
	void addModel(Model* model);
};