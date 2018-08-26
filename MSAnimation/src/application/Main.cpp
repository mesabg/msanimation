#include <Main.h>

[System::STAThread]
int main() {
	CoreDirector* coreDirector = new CoreDirector();
	MsCoreBuilder* msCoreBuilder = new MsCoreBuilder();

	coreDirector->setCoreBuilder(msCoreBuilder);
	coreDirector->buildCore();

	// Start main loop
	Core* core = coreDirector->getCore();
	core->broadcast("Core::initialize");

	// Finish main loop and clear memory
	core->broadcast("Core::finalize");
	delete coreDirector;
}