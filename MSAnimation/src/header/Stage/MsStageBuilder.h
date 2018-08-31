#pragma once

// Global includes
#include <string>
#include <iostream>
#include <memory>

// Local includes
#include <Stage/StageBuilder.h>

class MsStageBuilder : public StageBuilder {
public:
	MsStageBuilder();
	~MsStageBuilder();

	void buildCamera() override;
	void buildModels() override;
	void buildShader() override;
};