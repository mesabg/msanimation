#pragma once

// Global imports
#include <string>
#include <iostream>

// Local imports
#include <CoreMediator.h>

// Using spaces
using std::string;
using std::cout;
using std::endl;
using std::pair;

class Core : public CoreMediator {
private:

public:
	Core() {}
	~Core();

	//-- Override methods
	void add(CoreColleague *colleague) override;
	void send(string message, void* data, CoreColleague* colleague) override;
	void broadcast(std::string message, void* data = NULL) override;
};

