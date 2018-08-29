#pragma once

// Global includes
#include <string>
#include <iostream>
#include <vector>
#include <anttweakbar/AntTweakBar.h>

// Local includes
#include <Core/CoreColleague.h>
#include <Core/Core.h>

// Using spaces
using std::string;
using std::vector;
using std::map;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;
using std::cout;
using std::endl;

enum SelectOption {
	OPTION0,
	OPTION1,
	OPTION2,
	OPTION3,
	OPTION4,
	OPTION5,
	OPTION6,
	OPTION7,
	OPTION8,
	OPTION9,
	OPTION10,
	OPTION11,
	OPTION12,
	OPTION13,
	OPTION14,
	OPTION15,
	OPTION16,
	OPTION17,
	OPTION18,
	OPTION19,
	OPTION20,
};

class Sidebar : public CoreColleague {
private:
	map<string, TwBar*> bars;
	map<string, map<string, int> > options;

	// Methods
	void update();

public:
	Sidebar(Core* mediator);
	~Sidebar();

	// Overrides
	void send(string message, void* data) override;
	void receive(string message, void* data) override;

	// Methods
	void setWindowSize(int gWidth, int gHeight);
	void createBar(const string name);
	void setProperties(const string name, const vector<string>& properties);
	void setProperty(const string name, const string property);
	void addButton(const string name, const string options, void(*callback)(void*));
	void addSeparator(const string name);
	void addNumber(const string name, const string options, float* number);
	void addColor(const string name, const string options, vec3* color);
	void addVector(const string name, const string options, vec3* vector);
	void addRotation(const string name, const string options, quat* quaternion);
	void addCheck(const string name, const string options, bool* check);
	void addSelect(const string name, const string options, const string title, const vector<string>&labels, SelectOption* selectedOption);
};