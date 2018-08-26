#pragma once
#include <string>
#include <iostream>

#include <SidebarBuilder.h>

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
