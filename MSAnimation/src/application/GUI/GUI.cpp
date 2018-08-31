#include <GUI/GUI.h>

// General main initializations
GUI* GUI::uniqueGUI = NULL;
GLFWwindow* GUI::gWindow = NULL;
int GUI::gWidth = 1440;
int GUI::gHeight = 900;
double GUI::lastFrameTime = GUI::getCurrentTime();
double GUI::delta = 0.0f;


GUI::GUI(Core* mediator): CoreColleague(mediator) 
{
	if (!initGlfw() || glewInit() != GLEW_OK) exit(1);
}

GUI::~GUI() 
{
	glfwDestroyWindow(GUI::gWindow);
	glfwTerminate();
}

double GUI::getCurrentTime()
{
	return glfwGetTime() * 1000/*/glfwGetTimerValue()*/;
}

double GUI::getFrameTimeSeconds()
{
	return delta;
}

GUI* GUI::instance(Core* mediator) 
{
	if (!uniqueGUI)
		uniqueGUI = new GUI(mediator);
	return uniqueGUI;
}


void GUI::destroy() 
{
	if (!uniqueGUI) return;
	uniqueGUI->~GUI();
}


float GUI::getHeight() 
{
	return (float)GUI::gHeight;
}


float GUI::getWidth() 
{
	return (float)GUI::gWidth;
}


GLFWwindow * GUI::getWindow() 
{
	return GUI::gWindow;
}


void GUI::setSize(const float width, const float height) 
{
	reshape(GUI::gWindow, (int)width, (int)height);
}

bool GUI::initGlfw() 
{
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_SAMPLES, 4);
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GUI::gWindow = glfwCreateWindow(GUI::gWidth, GUI::gHeight, "MSAnimation", NULL, NULL);

	if (!GUI::gWindow) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(GUI::gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(GUI::gWindow, (vidMode->width - GUI::gWidth) >> 1, (vidMode->height - GUI::gHeight) >> 1);

	//-- GLFW Callbacks
	glfwSetWindowSizeCallback(GUI::gWindow, reshape);
	glfwSetKeyCallback(GUI::gWindow, keyInput);
	glfwSetMouseButtonCallback(GUI::gWindow, mouseButton);
	glfwSetCursorPosCallback(GUI::gWindow, cursorPos);
	glfwSetScrollCallback(GUI::gWindow, scroll);

	this->send("GUI::windowStarted", (void*)(new int[2]{ GUI::gWidth, GUI::gHeight }));

	return true;
}


void GUI::reshape(GLFWwindow *window, int width, int height) 
{
	GUI* localUserInterface = GUI::instance(NULL);

	GUI::gWidth = width;
	GUI::gHeight = height;
	glViewport(0, 0, GUI::gWidth, GUI::gHeight);

	// Signals
	localUserInterface->send("GUI::windowSize", (void*)(new int[2]{ GUI::gWidth, GUI::gHeight }) );
}


/*Visual Callbacks*/
void GUI::cursorPos(GLFWwindow* window, double x, double y) 
{
	GUI *localUserInterface = GUI::instance(NULL);

	int stateMouseButtonRight = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	int stateMouseButtonLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	int x1 = (int)x;
	int y1 = (int)y;

	//-- Signals
	localUserInterface->send("GUI::cursorPos", (void*)(new int[2]{ x1, y1 }));
}


void GUI::mouseButton(GLFWwindow* window, int button, int action, int mods) 
{
	GUI *localUserInterface = GUI::instance(NULL);

	// Signals
	localUserInterface->send("GUI::mouseButton", (void*)(new int[2]{ button, action }));
}


void GUI::keyInput(GLFWwindow * window, int key, int scancode, int action, int mods) 
{
	GUI *localUserInterface = GUI::instance(NULL);
	
	// Signals
	localUserInterface->send("GUI::keyInput", (void*)(new int[2]{ key , action }));
}

void GUI::scroll(GLFWwindow * window, double mod, double scroll) 
{
	GUI *localUserInterface = GUI::instance(NULL);
	int scroll_value = (int)scroll;

	// Signals
	localUserInterface->send("GUI::scroll", (void*)&scroll_value);
}

void GUI::send(string message, void * data)
{
	this->mediator->send(message, data, this);
}

void GUI::receive(string message, void * data)
{
	if (message == "Core::initialize") {
		this->listGraphicsResources();
		this->infinity();
	}
}

void GUI::render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update signal
	this->send("GUI::render", NULL);

	double currentFrameTime = getCurrentTime();
	delta = (currentFrameTime - lastFrameTime) / 1000.0f;
	lastFrameTime = currentFrameTime;
}

void GUI::listGraphicsResources()
{
	// Graphic Card Info
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

int GUI::infinity()
{
	while (!glfwWindowShouldClose(this->getWindow())) {
		this->render();
		glfwSwapBuffers(this->getWindow());
		glfwPollEvents();
	}
	return EXIT_SUCCESS;
}

int GUI::finish()
{
	this->destroy();
	this->send("GUI::destroy", NULL);
	return EXIT_SUCCESS;
}



//-- Mouse Class
vec2 Mouse::position = vec2();
double Mouse::x = 0.0f;
double Mouse::y = 0.0f;

Mouse::Mouse() {}

Mouse::~Mouse() {}

vec2 Mouse::getPosition() 
{
	glfwGetCursorPos(GUI::getWindow(), &Mouse::x, &Mouse::y);
	Mouse::position.x = (float)Mouse::x;
	Mouse::position.y = (float)Mouse::y;
	return position;
}
