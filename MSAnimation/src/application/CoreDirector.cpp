#include <CoreDirector.h>

CoreDirector::~CoreDirector()
{
	delete this->coreBuilder;
}

void CoreDirector::setCoreBuilder(CoreBuilder* coreBuilder)
{
	this->coreBuilder = coreBuilder;
}

Core* CoreDirector::getCore()
{
	return this->coreBuilder->getCore();
}

void CoreDirector::buildCore()
{
	this->coreBuilder->createNewCore();
	this->coreBuilder->buildCoreColleagues();
}
