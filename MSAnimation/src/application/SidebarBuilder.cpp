#include <SidebarBuilder.h>

SidebarBuilder::~SidebarBuilder()
{
	delete this->sidebar;
}

Sidebar* SidebarBuilder::getSidebar()
{
	return this->sidebar;
}

void SidebarBuilder::createNewSidebar(Core* mediator)
{
	this->sidebar = new Sidebar(mediator);
}
