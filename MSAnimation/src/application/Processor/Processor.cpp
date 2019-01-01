#include <Processor/Processor.h>

// General main initializations
Processor* Processor::uniqueProcessor = NULL;


Processor::Processor(Core* mediator) : CoreColleague(mediator)
{

}

Processor::~Processor()
{

}


Processor* Processor::instance(Core* mediator)
{
	if (!uniqueProcessor)
		uniqueProcessor = new Processor(mediator);
	return uniqueProcessor;
}


void Processor::destroy()
{
	if (!uniqueProcessor) return;
	uniqueProcessor->~Processor();
}


void Processor::send(string message, void * data)
{
	this->mediator->send(message, data, this);
}


void Processor::receive(string message, void * data)
{
	if (message == "Core::initialize") {
		//-- Do something
	}
}