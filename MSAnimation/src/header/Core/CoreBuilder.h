#pragma once

// Global includes
#include <string>
#include <iostream>
#include <memory>

// Local includes
#include <Core/Core.h>
#include <Core/CoreMediator.h>

class CoreBuilder {
protected:
	Core* core;

public:
	CoreBuilder(){}
	~CoreBuilder();

	Core* getCore();
	void createNewCore();

	virtual void buildCoreColleagues() = 0;
};