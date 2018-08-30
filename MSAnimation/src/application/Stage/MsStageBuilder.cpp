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
}

void MsStageBuilder::buildModels()
{
	// Create some models
}