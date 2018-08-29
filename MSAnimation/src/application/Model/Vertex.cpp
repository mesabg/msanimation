#include <Model/Vertex.h>

Vertex::Vertex()
{
	this->position = vec3(0.0f, 0.0f, 0.0f);
	this->normal = vec3(0.0f, 0.0f, 0.0f);
	this->texCoords = vec2(0.0f, 0.0f);
}

Vertex::~Vertex()
{
	// Do something
}

vec3 Vertex::getPosition()
{
	return this->position;
}

vec3 Vertex::getNormal()
{
	return this->normal;
}

vec2 Vertex::getTexCoords()
{
	return this->texCoords;
}

void Vertex::setPosition(vec3 position)
{
	this->position = position;
}

void Vertex::setNormal(vec3 normal)
{
	this->normal = normal;
}

void Vertex::setTexCoords(vec2 texCoords)
{
	this->texCoords = texCoords;
}
