#include <Stage/MsStageBuilder.h>

MsStageBuilder::MsStageBuilder()
{
	// Do something
}

MsStageBuilder::~MsStageBuilder()
{
	// Do something
}

void MsStageBuilder::buildCamera()
{
	// Create camera
	Camera* camera = Camera::instance(vec3(0.0f, 0.0f, 3.0f));
	this->stage->setCamera(camera);
	this->stage->updateProjection(1440, 900);
}

void MsStageBuilder::buildModels()
{
	// Create some models
}

void MsStageBuilder::buildShader()
{
	// Create simple shader
	Shader* shader = new Shader();
	shader->load({
		new ShaderPath("../src/shader/Basic/basic.vert", VERTEX),
		new ShaderPath("../src/shader/Basic/basic.frag", FRAGMENT)
	});
	shader->create_link();
	shader->enable();
	shader->disable();
	this->stage->setShader(shader);
}
