#pragma once
#include <string>
#include <iostream>
#include <memory>

#include <SidebarBuilder.h>
#include <GUI.h>

class MsSidebarBuilder : public SidebarBuilder {
public:
	MsSidebarBuilder();
	~MsSidebarBuilder();

	void buildWindowSize() override;
	void buildBars() override;
	void buildProperties() override;
	void buildArtifacts() override;
};