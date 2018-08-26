#include <Core/CoreBuilder.h>

CoreBuilder::~CoreBuilder()
{
	delete this->core;
}

Core* CoreBuilder::getCore()
{
	return this->core;
}

void CoreBuilder::createNewCore()
{
	this->core = new Core();
}
