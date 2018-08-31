#pragma once

// Global includes
#include <string>
#include <iostream>

// Local includes
#include <Stage/Stage.h>

class StageBuilder {
protected:
	Stage * stage;

public:
	StageBuilder() {}
	~StageBuilder();

	Stage* getStage();
	void createNewStage(Core* mediator);

	virtual void buildCamera() = 0;
	virtual void buildShader() = 0;
	virtual void buildModels() = 0;
};