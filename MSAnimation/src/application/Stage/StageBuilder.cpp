#include <Stage/StageBuilder.h>

StageBuilder::~StageBuilder()
{
	delete this->stage;
}

Stage* StageBuilder::getStage()
{
	return this->stage;
}

void StageBuilder::createNewStage(Core* mediator)
{
	this->stage = new Stage(mediator);
}
