#include <FileManager/FileManagerDirector.h>

FileManagerDirector::~FileManagerDirector()
{
	delete this->fileManagerBuilder;
}

void FileManagerDirector::setFileManagerBuilder(FileManagerBuilder* fileManagerBuilder)
{
	this->fileManagerBuilder = fileManagerBuilder;
}

FileManager* FileManagerDirector::getFileManager()
{
	return this->fileManagerBuilder->getFileManager();
}

void FileManagerDirector::buildFileManager(Core* mediator)
{
	this->fileManagerBuilder->createNewFileManager(mediator);
	this->fileManagerBuilder->buildAvailableExtentions();
}
