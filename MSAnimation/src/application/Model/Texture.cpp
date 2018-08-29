#include <Model/Texture.h>

Texture::Texture()
{
	this->id = 0;
	this->type = "";
	this->path = "";
}

Texture::~Texture()
{
	// Do something
}

GLuint Texture::getId()
{
	return this->id;
}

string Texture::getType()
{
	return this->type;
}

aiString Texture::getPath()
{
	return this->path;
}

void Texture::setId(GLuint id)
{
	this->id = id;
}

void Texture::setType(string type)
{
	this->type = type;
}

void Texture::setPath(aiString path)
{
	this->path = path;
}
