#include <FileManagerBuilder.h>

FileManagerBuilder::~FileManagerBuilder()
{
	delete this->fileManager;
}

FileManager* FileManagerBuilder::getFileManager()
{
	return this->fileManager;
}

void FileManagerBuilder::createNewFileManager(Core* mediator)
{
	this->fileManager = new FileManager(mediator);
}
