#include <Sidebar/SidebarDirector.h>

SidebarDirector::~SidebarDirector()
{
	delete this->sidebarBuilder;
}

void SidebarDirector::setSidebarBuilder(SidebarBuilder* sidebarBuilder)
{
	this->sidebarBuilder = sidebarBuilder;
}

Sidebar* SidebarDirector::getSidebar()
{
	return this->sidebarBuilder->getSidebar();
}

void SidebarDirector::buildSidebar(Core* mediator)
{
	this->sidebarBuilder->buildWindowSize();
	this->sidebarBuilder->createNewSidebar(mediator);
	this->sidebarBuilder->buildBars();
	this->sidebarBuilder->buildProperties();
	this->sidebarBuilder->buildArtifacts();
}
