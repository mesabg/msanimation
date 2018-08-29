#include <Core/MsCoreBuilder.h>

MsCoreBuilder::MsCoreBuilder()
{

}

MsCoreBuilder::~MsCoreBuilder()
{

}

void MsCoreBuilder::buildCoreColleagues()
{
	// Build GUI
	GUI* gui = GUI::instance(this->core);

	// Build Sidebar
	SidebarDirector* sidebarDirector = new SidebarDirector();
	MsSidebarBuilder* msSidebarBuilder = new MsSidebarBuilder();
	sidebarDirector->setSidebarBuilder(msSidebarBuilder);
	sidebarDirector->buildSidebar(this->core);
	Sidebar* sidebar = sidebarDirector->getSidebar();

	// Build File Manager
	FileManagerDirector* fileManagerDirector = new FileManagerDirector();
	MsFileManagerBuilder* msFileManagerBuilder = new MsFileManagerBuilder();
	fileManagerDirector->setFileManagerBuilder(msFileManagerBuilder);
	fileManagerDirector->buildFileManager(this->core);
	FileManager* fileManager = fileManagerDirector->getFileManager();

	// Build Model Manager
	ModelManager* modelManager = ModelManager::instance(this->core);

	// Add instances to Core Mediator
	this->core->add(sidebar);
	this->core->add(fileManager);
	this->core->add(modelManager);
	this->core->add(gui);
}
