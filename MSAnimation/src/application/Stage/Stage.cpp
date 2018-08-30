#include <Stage/Stage.h>

void Stage::render()
{
	// Render the entire stage
}

Stage::Stage(Core* mediator):CoreColleague(mediator)
{
	// Do something
}

Stage::~Stage()
{
	for (Model* model : this->models) {
		delete model;
	}
	this->models.clear();
	this->camera->destroy();
}

void Stage::send(string message, void * data)
{
	this->mediator->send(message, data, this);
}

void Stage::receive(string message, void * data)
{
	// Receive and proccess signals
	if (message == "ModelManager::modelLoaded") {
		Model* model = (Model*)data;
		this->addModel(model);
	}

	if (message == "GUI::render") {
		this->render();
	}
}

void Stage::setCamera(Camera * camera)
{
	this->camera = camera;
}

void Stage::addModel(Model * model)
{
	this->models.push_back(model);
}