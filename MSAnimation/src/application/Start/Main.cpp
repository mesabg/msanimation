#include <Start/Main.h>
#include <Eigen/Dense>
#include <igl/readOBJ.h>

[System::STAThread]
int main() {
	CoreDirector* coreDirector = new CoreDirector();
	MsCoreBuilder* msCoreBuilder = new MsCoreBuilder();

	coreDirector->setCoreBuilder(msCoreBuilder);
	coreDirector->buildCore();

	// Start main loop
	Core* core = coreDirector->getCore();
	core->broadcast("Core::initialize", (void*)(new float[2]{ GUI::getWidth(), GUI::getHeight() }));
	//string defaultModelPath = "../models/nanosuit/nanosuit.obj";
	//core->broadcast("FileManager::fileReaded", (void*)defaultModelPath.c_str());

	// Finish main loop and clear memory
	core->broadcast("Core::finalize");
	delete coreDirector;
	/*Eigen::MatrixXd V;
	Eigen::MatrixXi F;

	// Load a mesh in OFF format
	igl::readOBJ("../models/nanosuit/nanosuit.obj", V, F);

	// Plot the mesh
	cout << V.size() << endl;

	std::cin.get();*/
}