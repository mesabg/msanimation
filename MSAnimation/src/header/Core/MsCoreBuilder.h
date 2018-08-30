#pragma once

// Global includes
#include <string>
#include <iostream>

// Local includes
#include <Core/CoreBuilder.h>
#include <GUI/GUI.h>
#include <Sidebar/SidebarDirector.h>
#include <Sidebar/MsSidebarBuilder.h>
#include <FileManager/FileManagerDirector.h>
#include <FileManager/MsFileManagerBuilder.h>
#include <ModelManager/ModelManager.h>
#include <Stage/StageDirector.h>
#include <Stage/MsStageBuilder.h>

class MsCoreBuilder : public CoreBuilder {
public:
	MsCoreBuilder();
	~MsCoreBuilder();

	void buildCoreColleagues() override;
};