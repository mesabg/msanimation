#include <Sidebar/Sidebar.h>

void Sidebar::update()
{
	TwDraw();
}

Sidebar::Sidebar(Core * mediator):CoreColleague(mediator) 
{
	if (!TwInit(TW_OPENGL, NULL)) {
		cout << "Side Bar Not Initiated\n";
	}
}

Sidebar::~Sidebar()
{
	TwTerminate();
}

void Sidebar::send(string message, void * data)
{
	this->mediator->send(message, data, this);
}

void Sidebar::receive(string message, void * data)
{
	if (message == "GUI::render") {
		this->update();
	} 

	if (message == "GUI::windowSize") {
		int gWidth = ((int*)data)[0];
		int gHeight = ((int*)data)[1];
		TwWindowSize(gWidth, gHeight);
	}

	if (message == "GUI::cursorPos") {
		int x = ((int*)data)[0];
		int y = ((int*)data)[1];
		TwEventMousePosGLFW(x, y);
	}

	if (message == "GUI::mouseButton") {
		int button = ((int*)data)[0];
		int action = ((int*)data)[1];
		TwEventMouseButtonGLFW(button, action);
	}

	if (message == "GUI::keyInput") {
		int key = ((int*)data)[0];
		int action = ((int*)data)[1];
		if (TwEventKeyGLFW(key, action)) return;
	}

	if (message == "GUI::Scroll") {
		int scroll = *((int*)data);
		TwEventMouseWheelGLFW((int)scroll);
	}
	
}

void Sidebar::setWindowSize(int gWidth, int gHeight)
{
	TwWindowSize(gWidth, gHeight);
}

void Sidebar::createBar(const string name)
{
	this->bars[name] = TwNewBar(name.c_str());

	// Increment
	this->options[name]["button"] = 0;
	this->options[name]["separator"] = 0;
	this->options[name]["number"] = 0;
	this->options[name]["color"] = 0;
	this->options[name]["vector"] = 0;
	this->options[name]["rotation"] = 0;
	this->options[name]["check"] = 0;
	this->options[name]["select"] = 0;
}

void Sidebar::setProperties(const string name, const vector<string>& properties)
{
	for (const string property : properties) {
		TwDefine((name +" "+ property).c_str());
	}
}

void Sidebar::setProperty(const string name, const string property)
{
	TwDefine((name +" "+ property).c_str());
}

void Sidebar::addButton(const string name, const string options, void(*callback)(void *))
{
	if (this->bars[name] == NULL) {
		// Main error
		cout << "Bar " << name << " does not exits in sidebar object.\n";
		return;
	}

	// Build Opject
	this->options[name]["button"]++;
	string index = std::to_string(this->options[name]["button"]);
	TwAddButton(this->bars[name], (name+"Button"+index).c_str(), callback, (void*)this, options.c_str());
}

void Sidebar::addSeparator(const string name)
{
	if (this->bars[name] == NULL) {
		// Main error
		cout << "Bar " << name << " does not exits in sidebar object.\n";
		return;
	}

	// Build Opject
	this->options[name]["separator"]++;
	string index = std::to_string(this->options[name]["separator"]);
	TwAddSeparator(this->bars[name], (name + "Separator" + index).c_str(), "");
}

void Sidebar::addNumber(const string name, const string options, float * number)
{
	if (this->bars[name] == NULL) {
		// Main error
		cout << "Bar " << name << " does not exits in sidebar object.\n";
		return;
	}

	// Build Opject
	this->options[name]["number"]++;
	string index = std::to_string(this->options[name]["number"]);
	TwAddVarRW(this->bars[name], (name + "Number" + index).c_str(), TW_TYPE_FLOAT, number, options.c_str());
}

void Sidebar::addColor(const string name, const string options, vec3 * color)
{
	if (this->bars[name] == NULL) {
		// Main error
		cout << "Bar " << name << " does not exits in sidebar object.\n";
		return;
	}

	// Build Opject
	this->options[name]["color"]++;
	string index = std::to_string(this->options[name]["color"]);
	TwAddVarRW(this->bars[name], (name + "Color" + index).c_str(), TW_TYPE_COLOR3F, color, options.c_str());
}

void Sidebar::addVector(const string name, const string options, vec3 * vector)
{
	if (this->bars[name] == NULL) {
		// Main error
		cout << "Bar " << name << " does not exits in sidebar object.\n";
		return;
	}

	// Build Opject
	this->options[name]["vector"]++;
	string index = std::to_string(this->options[name]["vector"]);
	TwAddVarRW(this->bars[name], (name + "Vector" + index).c_str(), TW_TYPE_DIR3F, vector, options.c_str());
}

void Sidebar::addRotation(const string name, const string options, quat * quaternion)
{
	if (this->bars[name] == NULL) {
		// Main error
		cout << "Bar " << name << " does not exits in sidebar object.\n";
		return;
	}

	// Build Opject
	this->options[name]["rotation"]++;
	string index = std::to_string(this->options[name]["rotation"]);
	TwAddVarRW(this->bars[name], (name + "Rotation" + index).c_str(), TW_TYPE_QUAT4F, quaternion, options.c_str());
}

void Sidebar::addCheck(const string name, const string options, bool * check)
{
	if (this->bars[name] == NULL) {
		// Main error
		cout << "Bar " << name << " does not exits in sidebar object.\n";
		return;
	}

	// Build Opject
	this->options[name]["check"]++;
	string index = std::to_string(this->options[name]["check"]);
	TwAddVarRW(this->bars[name], (name + "Check" + index).c_str(), TW_TYPE_BOOLCPP, check, options.c_str());
}

void Sidebar::addSelect(const string name, const string options, const string title, const vector<string>& labels, SelectOption * selectedOption)
{
	if (this->bars[name] == NULL) {
		// Main error
		cout << "Bar " << name << " does not exits in sidebar object.\n";
		return;
	}

	if (labels.size() > 20) {
		// Overhead
		cout << "Max options are 20, please change the limit" << endl;
	}

	// Initialize options
	size_t size = labels.size();
	TwEnumVal* selectTypeSelector = new TwEnumVal[size];
	for (int i = 0; i<size; i++){
		selectTypeSelector[i] = { (SelectOption)i, labels[i].c_str() };
	}
	TwType selectType = TwDefineEnum(title.c_str(), selectTypeSelector, 3);

	// Build Opject
	this->options[name]["select"]++;
	string index = std::to_string(this->options[name]["select"]);
	TwAddVarRW(this->bars[name], (name + "Select" + index).c_str(), selectType, selectedOption, NULL);
}
