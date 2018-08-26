#pragma once

// Global includes
#include <string>
#include <iostream>

// Local includes
#include <Sidebar/Sidebar.h>

class SidebarBuilder {
protected:
	Sidebar * sidebar;

public:
	SidebarBuilder() {}
	~SidebarBuilder();

	Sidebar* getSidebar();
	void createNewSidebar(Core* mediator);

	virtual void buildWindowSize() = 0;
	virtual void buildBars() = 0;
	virtual void buildProperties() = 0;
	virtual void buildArtifacts() = 0;
};