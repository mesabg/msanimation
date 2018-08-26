#pragma once

// Global includes
#include <string>
#include <iostream>

// Local includes
#include <Sidebar/SidebarBuilder.h>

class SidebarDirector {
private:
	SidebarBuilder * sidebarBuilder;

public:
	SidebarDirector() {}
	~SidebarDirector();

	void setSidebarBuilder(SidebarBuilder* sidebarBuilder);
	Sidebar* getSidebar();
	void buildSidebar(Core* mediator);
};
