#include <Model/Shader.h>

bool Shader::loadFile(string strFilename, GLuint iHandle)
{
	ifstream shaderSource(strFilename.c_str());
	if (!shaderSource.is_open())
	{
		cerr << " File not found " << strFilename.c_str() << endl;
		return false;
	}
	// now read in the data
	string strSource = string((istreambuf_iterator<char>(shaderSource)), istreambuf_iterator<char>());
	shaderSource.close();
	strSource += "\0";
	//pass the code to OGL
	const char* data = strSource.c_str();
	glShaderSource(iHandle, 1, &data, NULL);
	return true;
}

void Shader::checkLinkingErrors()
{
	GLint infologLength = 0;
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1)
	{
		char *infoLog = new char[infologLength];
		GLint charsWritten = 0;

		glGetProgramInfoLog(this->program, infologLength, &charsWritten, infoLog);

		std::cerr << infoLog << std::endl;
		delete[] infoLog;
		glGetProgramiv(this->program, GL_LINK_STATUS, &infologLength);
		if (infologLength == GL_FALSE)
		{
			std::cerr << "Program link failed exiting \n";
			exit(EXIT_FAILURE);
		}
	}
}

Shader::Shader()
{
	shaders.clear();
}

Shader::~Shader()
{
	shaders.clear();
	if (this->program > 0)
	{
		glDeleteProgram(this->program);
		cout << "Program deleted! " << endl;
	}
}

GLuint Shader::getProgram()
{
	return this->program;
}

void Shader::setProgram(GLuint program)
{
	this->program = program;
}

void Shader::load(vector< ShaderPath* > paths)
{
	for (ShaderPath* path : paths) {
		this->load(path);
	}
}

void Shader::load(ShaderPath * path)
{
	GLuint hShader = 0;
	GLint status;

	//Create shader object
	switch (path->getType())
	{
		case VERTEX: { hShader = glCreateShader(GL_VERTEX_SHADER); break; }
		case FRAGMENT: { hShader = glCreateShader(GL_FRAGMENT_SHADER); break; }
		case GEOMETRY: { hShader = glCreateShader(GL_GEOMETRY_SHADER); break; }
		case TESSELLATION: { hShader = 0; std::cerr << "not implemented.... yet :-)" << std::endl; }
	}

	if (this->loadFile(path->getSource(), hShader))
	{
		//now compile the shader
		glCompileShader(hShader);
		glGetShaderiv(hShader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			char infoLog[1024];
			glGetShaderInfoLog(hShader, 1024, NULL, infoLog);
			cout << "The shader at " << path->getSource().c_str() << " failed to compile with the following errors:" << endl
				<< infoLog << endl;
			glDeleteShader(hShader);
		}
		else	//here, everything is OK
		{
			cout << "The shader at " << path->getSource().c_str() << " was compiled without errors." << endl;
			this->shaders.push_back(hShader);
		}
	}
	else
	{
		std::cerr << "something wrong loading the shader located in " << path->getSource().c_str() << "." << std::endl;
		glDeleteShader(hShader);
	}
}

void Shader::create()
{
	this->program = glCreateProgram();

	//attach the shaders
	for (GLuint shader : this->shaders) {
		glAttachShader(this->program, shader);
	}

	//delete the shaders
	for (GLuint shader : this->shaders) {
		glDeleteShader(shader);
	}
	checkLinkingErrors();
}

void Shader::create_link()
{
	this->program = glCreateProgram();

	//attach the shaders
	for (GLuint shader : this->shaders) {
		glAttachShader(this->program, shader);
	}

	//link the program
	glLinkProgram(this->program);

	//check errors on linking
	checkLinkingErrors();

	//delete the shaders
	for (GLuint shader : this->shaders) {
		glDeleteShader(shader);
	}
}

void Shader::link(vector<string> attributes, vector<string> uniforms)
{
	//Bind attributes and uniforms
	int i = 0;
	for (int i = 0; i < (int)attributes.size(); i++)
		glBindAttribLocation(this->program, i, attributes[i].c_str());

	for (int j = 0; j < (int)uniforms.size(); i++, j++)
		glBindAttribLocation(this->program, i, uniforms[j].c_str());

	//link the program
	glLinkProgram(this->program);

	//check errors on linking
	checkLinkingErrors();
}

void Shader::enable()
{
	glUseProgram(this->program);
}

void Shader::disable()
{
	glUseProgram(0);
}

