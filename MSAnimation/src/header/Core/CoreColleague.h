#pragma once

// Global includes
#include <glew\glew.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

// Using spaces
using std::string;
using std::vector;
using std::map;
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;


// For compiler
class CoreMediator;

class CoreColleague {
protected:
	CoreMediator* mediator;

public:
	CoreColleague(CoreMediator* mediator) : mediator(mediator) {}
	~CoreColleague() {}
	
	// Mediate functions
	virtual void send(string message, void* data) = 0;
	virtual void receive(string message, void* data) = 0;
};