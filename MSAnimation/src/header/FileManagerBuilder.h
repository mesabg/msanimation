#pragma once
#include <string>
#include <iostream>

#include <FileManager.h>

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