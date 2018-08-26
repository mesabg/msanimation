#pragma once

// Global includes
#include <string>
#include <iostream>

// Local includes
#include <FileManager/FileManager.h>

class FileManagerBuilder {
protected:
	FileManager * fileManager;

public:
	FileManagerBuilder() {}
	~FileManagerBuilder();

	FileManager* getFileManager();
	void createNewFileManager(Core* mediator);

	virtual void buildAvailableExtentions() = 0;
	virtual void buildInitialDirectory() = 0;
};