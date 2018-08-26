#pragma once
#include <string>
#include <iostream>

#include <CoreBuilder.h>

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