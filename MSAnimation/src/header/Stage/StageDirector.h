#pragma once

// Global includes
#include <string>
#include <iostream>

// Local includes
#include <Stage/StageBuilder.h>

class StageDirector {
private:
	StageBuilder * stageBuilder;

public:
	StageDirector() {}
	~StageDirector();

	void setStageBuilder(StageBuilder* stageBuilder);
	Stage* getStage();
	void buildStage(Core* mediator);
};
