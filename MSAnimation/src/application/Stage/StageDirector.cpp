#include <Stage/StageDirector.h>

StageDirector::~StageDirector()
{
	delete this->stageBuilder;
}

void StageDirector::setStageBuilder(StageBuilder* stageBuilder)
{
	this->stageBuilder = stageBuilder;
}

Stage* StageDirector::getStage()
{
	return this->stageBuilder->getStage();
}

void StageDirector::buildStage(Core* mediator)
{
	this->stageBuilder->createNewStage(mediator);
	this->stageBuilder->buildCamera();
	this->stageBuilder->buildModels();
}
