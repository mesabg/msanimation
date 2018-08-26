#pragma once

// Global includes
#include <string>
#include <iostream>

// Local includes
#include <Core/CoreBuilder.h>

class CoreDirector {
private:
	CoreBuilder* coreBuilder;

public:
	CoreDirector(){}
	~CoreDirector();

	void setCoreBuilder(CoreBuilder* coreBuilder);
	Core* getCore();
	void buildCore();
};