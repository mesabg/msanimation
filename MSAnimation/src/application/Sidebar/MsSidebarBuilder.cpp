#include <Sidebar/MsSidebarBuilder.h>

MsSidebarBuilder::MsSidebarBuilder()
{

}

MsSidebarBuilder::~MsSidebarBuilder()
{

}

void MsSidebarBuilder::buildWindowSize()
{
	this->sidebar->setWindowSize(1440, 900);
}

void MsSidebarBuilder::buildBars()
{
	this->sidebar->createBar("Menu");
}

void MsSidebarBuilder::buildProperties()
{
	this->sidebar->setProperties("Menu", {
		"refresh = '0.0001f'",
		"resizable = false",
		"fontresizable = false",
		"movable = false",
		"visible = true",
		"position = '20 20'",
		"size = '280 230'",
		"refresh = '0.0001f'",
	});
}

void MsSidebarBuilder::buildArtifacts()
{
	this->sidebar->addButton(
		"Menu", 
		"label='Select a model' group='Model loader' help='Select a model from your directory'", 
		[](void* clientData) {
			Sidebar* sidebar = (Sidebar*)clientData;
			sidebar->send("Sidebar::readFile", NULL);
		}
	);

	this->sidebar->addSeparator("Menu");

	SelectOption* selectedOption = new SelectOption();
	*(selectedOption) = OPTION0;
	this->sidebar->addSelect(
		"Menu",
		"label='Select a model' group='Model loader' help='Select a model from your directory'",
		"Type",
		{
			"Type one",
			"Type two",
			"Type three",
		},
		selectedOption
	);
}