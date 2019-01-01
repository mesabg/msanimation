#include <Stage/Stage.h>

void Stage::render()
{
	// Render the entire stage
	
	// Enable the shader
	this->shader->enable();

	// Bind view and projection matrices
	glm::mat4 view = this->camera->getViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(this->shader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(this->projection));
	glUniformMatrix4fv(glGetUniformLocation(this->shader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	for (Model* modelObject : this->models) {
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(this->shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		modelObject->render(shader);
	}
	this->shader->disable();
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
	if (message == "Core::initialize") {
		const int width = (int)((float*)data)[0];
		const int height = (int)((float*)data)[1];
		this->updateProjection(width, height);
	}

	if (message == "GUI::windowSize") {
		const int width = ((int*)data)[0];
		const int height = ((int*)data)[0];
		this->updateProjection(width, height);
	}

	if (message == "ModelManager::modelLoaded") {
		Model* model = (Model*)data;
		this->addModel(model);
	}

	if (message == "GUI::render") {
		this->render();
	}

	if (message == "GUI::keyInput") {
		const int key = ((int*)data)[0];
		const int action = ((int*)data)[1];

		if ((key == GLFW_KEY_W || key == GLFW_KEY_UP) && action == GLFW_PRESS)
			this->camera->processKeyboard(FORWARD, 5.0f);
		
		if ((key == GLFW_KEY_S || key == GLFW_KEY_DOWN) && action == GLFW_PRESS)
			this->camera->processKeyboard(BACKWARD, 5.0f);
		
		if ((key == GLFW_KEY_A || key == GLFW_KEY_LEFT) && action == GLFW_PRESS)
			this->camera->processKeyboard(LEFT, 5.0f);
		
		if ((key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) && action == GLFW_PRESS) 
			this->camera->processKeyboard(RIGHT, 5.0f);
	}
}

void Stage::setCamera(Camera * camera)
{
	this->camera = camera;
}

void Stage::setShader(Shader * shader)
{
	this->shader = shader;
}

void Stage::addModel(Model * model)
{
	this->models.push_back(model);
}

void Stage::updateProjection(const int width, const int height)
{
	this->projection = glm::perspective(this->camera->getZoom(), (float)width / (float)height, 0.1f, 100.0f);
}