#include <Model/ShaderPath.h>

ShaderPath::~ShaderPath()
{
	delete this->source;
}

GLchar * ShaderPath::getSource()
{
	return this->source;
}

ShaderType ShaderPath::getType()
{
	return this->type;
}

void ShaderPath::setSource(GLchar * source)
{
	this->source = source;
}

void ShaderPath::setType(ShaderType type)
{
	this->type = type;
}
