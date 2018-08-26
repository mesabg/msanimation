#pragma once

// Global includes
#include <vector>
#include <string>

// Local includes
#include <Core/CoreColleague.h>


class CoreMediator {
protected:
	std::vector<CoreColleague*> colleagues;
	CoreMediator() {}
	~CoreMediator() {};

public:
	virtual void add(CoreColleague *colleague) = 0;
	virtual void send(string message, void* data, CoreColleague* colleague) = 0;
	virtual void broadcast(string message, void* data = NULL) = 0;
};