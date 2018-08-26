#pragma once
#include <string>
#include <iostream>

#include <FileManagerBuilder.h>

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
