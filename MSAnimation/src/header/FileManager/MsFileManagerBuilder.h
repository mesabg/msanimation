#pragma once

// Global includes
#include <string>
#include <iostream>
#include <memory>

// Local includes
#include <FileManager/FileManagerBuilder.h>
#include <GUI/GUI.h>

class MsFileManagerBuilder : public FileManagerBuilder {
public:
	MsFileManagerBuilder();
	~MsFileManagerBuilder();

	void buildAvailableExtentions() override;
	void buildInitialDirectory() override;
};