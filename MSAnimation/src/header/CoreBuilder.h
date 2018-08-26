#pragma once
#include <string>
#include <iostream>
#include <memory>

#include <Core.h>
#include <CoreMediator.h>

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