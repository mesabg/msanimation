#pragma once
#include <Core/Core.h>

Core::~Core()
{
	for (CoreColleague* colleague : this->colleagues) {
		delete colleague;
	}
	this->colleagues.empty();
}

void Core::add(CoreColleague* colleague)
{
	this->colleagues.push_back(colleague);
}

void Core::send(string message, void * data, CoreColleague * colleague)
{
	// Communication logic
	for (CoreColleague* colleague_ : this->colleagues) {
		if (colleague_ != colleague)
			colleague_->receive(message, data);
	}
}


void Core::broadcast(string message, void* data) 
{
	// Send message to everyone
	for (CoreColleague* colleague : this->colleagues) {
		colleague->receive(message, data);
	}
}