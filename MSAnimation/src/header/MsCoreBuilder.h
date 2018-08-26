#pragma once

// Global imports
#include <string>
#include <iostream>
#include <memory>

// Local imports
#include <CoreBuilder.h>
#include <GUI.h>
#include <SidebarDirector.h>
#include <MsSidebarBuilder.h>
#include <FileManagerDirector.h>
#include <MsFileManagerBuilder.h>

class MsCoreBuilder : public CoreBuilder {
public:
	MsCoreBuilder();
	~MsCoreBuilder();

	void buildCoreColleagues() override;
};