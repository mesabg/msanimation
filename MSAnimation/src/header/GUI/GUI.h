#pragma once

// Local includes
#include <Core/CoreColleague.h>
#include <Core/Core.h>

// Using spaces
using std::cout;
using std::endl;

class GUI : public CoreColleague
{
private:
	// Variables
	static GUI* uniqueGUI;
	static GLFWwindow* gWindow;
	static int gWidth;
	static int gHeight;

	// Inicializadores
	GUI(Core* mediator);
	~GUI();

	// Funciones propias
	bool initGlfw();

public:
	static double lastFrameTime;
	static double delta;
	static double getCurrentTime();
	static double getFrameTimeSeconds();

	// Get Instance
	static GUI* instance(Core* mediator);
	static void destroy();

	// Get functions
	static float getHeight();
	static float getWidth();
	static GLFWwindow* getWindow();

	// Set functions
	void setSize(const float width, const float height);

	// GLFW Callbacks
	static void reshape(GLFWwindow *window, int width, int height);
	static void cursorPos(GLFWwindow* window, double x, double y);
	static void mouseButton(GLFWwindow* window, int button, int action, int mods);
	static void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void scroll(GLFWwindow* window, double x, double y);

	// Override
	void send(string message, void* data) override;
	void receive(string message, void* data) override;

	// General functions
	void render();
	void listGraphicsResources();
	int finish();
	int infinity();
};


class Mouse {
private:
	static vec2 position;
	static double x, y;

public:
	Mouse();
	~Mouse();

	//-- Getters
	static vec2 getPosition();
};