#pragma once

// Global includes
#include <string>
#include <iostream>

// Local includes
#include <FileManager/FileManagerBuilder.h>

class FileManagerDirector {
private:
	FileManagerBuilder * fileManagerBuilder;

public:
	FileManagerDirector() {}
	~FileManagerDirector();

	void setFileManagerBuilder(FileManagerBuilder* fileManagerBuilder);
	FileManager* getFileManager();
	void buildFileManager(Core* mediator);
};
