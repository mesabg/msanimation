#pragma once

// Local Class Includes
#include <CoreColleague.h>
#include <Core.h>

// Using space
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;

class FileManager : public CoreColleague
{
private:
	// Variables declarations
	vector< map<string, string> > availableExtensions;
	string initialDirectory;

	// Main functions
	void read();
	void create(string type, void* data);

public:
	// Inicializadores
	FileManager(Core* mediator);
	~FileManager();

	// Override
	void send(string message, void* data) override;
	void receive(string message, void* data) override;

	// Builder Functions
	void setAvailableExtentions(const vector< map<string, string> >& availableExtensions);
	void setInitialDirectory(string initialDirectory);
};

// Helper functions
void MarshalString(String ^ s, string& os);