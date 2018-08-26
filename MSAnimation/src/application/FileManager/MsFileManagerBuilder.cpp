#include <FileManager/MsFileManagerBuilder.h>

MsFileManagerBuilder::MsFileManagerBuilder()
{

}

MsFileManagerBuilder::~MsFileManagerBuilder()
{

}

void MsFileManagerBuilder::buildAvailableExtentions()
{
	this->fileManager->setAvailableExtentions({
		{ { "title", "Object Model" }, { "acronym", "obj" } }
	});
}

void MsFileManagerBuilder::buildInitialDirectory()
{
	this->fileManager->setInitialDirectory("C:\\Users\\Equipo\\Desktop");
}
