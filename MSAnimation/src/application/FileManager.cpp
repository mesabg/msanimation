#include <FileManager.h>

void FileManager::read()
{
	// File loading
	String^ filePath;
	string fileNameString, type;
	OpenFileDialog^ openFile = gcnew OpenFileDialog;
	size_t length;

	// Available extentions
	string availableExtentions_ = "";
	for (map<string, string> extension : this->availableExtensions) {
		availableExtentions_ += extension["title"] + " (*." + extension["acronym"] + ")|*." + extension["acronym"] + "| ";
	}
	availableExtentions_.pop_back();
	availableExtentions_.pop_back();

	// Build initial directory
	openFile->InitialDirectory = gcnew String(this->initialDirectory.c_str());
	openFile->Filter = gcnew String(availableExtentions_.c_str());
	openFile->FilterIndex = 1;
	openFile->RestoreDirectory = true;

	if (openFile->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		filePath = openFile->FileName;
		MarshalString(filePath, fileNameString);
		length = fileNameString.length();
		type.push_back(fileNameString[length - 3]);
		type.push_back(fileNameString[length - 2]);
		type.push_back(fileNameString[length - 1]);
		
		// Send signal to mediator
		this->send("FileManager::fileReaded", (void*)fileNameString.c_str());
	}
}

void FileManager::create(string type, void * data)
{
	// Save data into a file
}

FileManager::FileManager(Core* mediator) : CoreColleague(mediator)
{
	// Do something
}

FileManager::~FileManager()
{
	// Do something
}

void FileManager::send(string message, void * data)
{
	this->mediator->send(message, data, this);
}

void FileManager::receive(string message, void * data)
{
	if (message == "Sidebar::readFile") {
		this->read();
	}
}

void FileManager::setAvailableExtentions(const vector< map<string, string> >& availableExtensions)
{
	this->availableExtensions.clear();
	for (map<string, string> extension : availableExtensions) {
		if (extension.find("title") == extension.end() || extension.find("acronym") == extension.end()) {
			cout << "{title} and {acronym} are not set properly\n";
			this->availableExtensions.clear();
			return;
		}

		map<string, string> element;
		element["title"] = extension["title"];
		element["acronym"] = extension["acronym"];
		this->availableExtensions.push_back(element);
	}
}

void FileManager::setInitialDirectory(string initialDirectory)
{
	this->initialDirectory = initialDirectory;
}

void MarshalString(String ^ s, string& os) 
{
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

