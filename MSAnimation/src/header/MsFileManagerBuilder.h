#pragma once
#include <string>
#include <iostream>
#include <memory>

#include <FileManagerBuilder.h>
#include <GUI.h>

class MsFileManagerBuilder : public FileManagerBuilder {
public:
	MsFileManagerBuilder();
	~MsFileManagerBuilder();

	void buildAvailableExtentions() override;
	void buildInitialDirectory() override;
};