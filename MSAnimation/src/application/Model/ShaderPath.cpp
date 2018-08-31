#include <Model/ShaderPath.h>

ShaderPath::ShaderPath(string source, ShaderType type)
{
	this->source = (GLchar*)source.c_str();
	this->type = type;
}

ShaderPath::~ShaderPath()
{
	// Do something
}

string ShaderPath::getSource()
{
	return this->source;
}

ShaderType ShaderPath::getType()
{
	return this->type;
}

void ShaderPath::setSource(string source)
{
	this->source = source;
}

void ShaderPath::setType(ShaderType type)
{
	this->type = type;
}
