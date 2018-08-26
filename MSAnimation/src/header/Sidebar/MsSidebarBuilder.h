#pragma once

// Global includes
#include <string>
#include <iostream>
#include <memory>

// Local includes
#include <Sidebar/SidebarBuilder.h>

class MsSidebarBuilder : public SidebarBuilder {
public:
	MsSidebarBuilder();
	~MsSidebarBuilder();

	void buildWindowSize() override;
	void buildBars() override;
	void buildProperties() override;
	void buildArtifacts() override;
};