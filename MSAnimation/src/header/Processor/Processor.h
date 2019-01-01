#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4146)

// Local includes
#include <Core/CoreColleague.h>
#include <Core/Core.h>
#include <Eigen/Dense>
#include <Eigen/Sparse>

// Using spaces
using std::cout;
using std::endl;

class Processor : public CoreColleague
{
private:
	// Variables
	static Processor* uniqueProcessor;

	// Inicializadores
	Processor(Core* mediator);
	~Processor();

public:
	// Get Instance
	static Processor* instance(Core* mediator);
	static void destroy();

	// Override
	void send(string message, void* data) override;
	void receive(string message, void* data) override;
};
