#include <Model/Shader.h>

Shader::Shader()
{
	// Create shader program
	this->program = glCreateProgram();
}

Shader::~Shader()
{
}

GLuint Shader::getProgram()
{
	return this->program;
}

void Shader::setProgram(GLuint program)
{
	this->program = program;
}

void Shader::load(vector< ShaderPath* >& paths)
{
	for (ShaderPath*path : paths) {
		// 1. Retrieve the source code from filePath
		string code;
		ifstream file;
	
		// ensures ifstream objects can throw exceptions:
		file.exceptions(ifstream::badbit);

		try
		{
			// Open files
			file.open(path->getSource());
			stringstream shaderStream;

			// Read file's buffer contents into streams
			shaderStream << file.rdbuf();

			// close file handlers
			file.close();

			// Convert stream into string
			code = shaderStream.str();
		}
		catch (ifstream::failure e)
		{
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
			continue;
		}

		const GLchar *shaderCode = code.c_str();

		// 2. Compile shaders
		GLuint shader;
		GLint success;
		GLchar infoLog[512];

		// Shader
		if (path->getType() == VERTEX) shader = glCreateShader(GL_VERTEX_SHADER);
		if (path->getType() == FRAGMENT) shader = glCreateShader(GL_FRAGMENT_SHADER);
		if (path->getType() == GEOMETRY) shader = glCreateShader(GL_GEOMETRY_SHADER);
		if (path->getType() == TESSELLATION) shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(shader, 1, &shaderCode, NULL);
		glCompileShader(shader);

		// Print compile errors if any
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
			continue;
		}

		// Shader program
		glAttachShader(this->program, shader);
		glLinkProgram(this->program);

		// Print linking errors if any
		glGetProgramiv(this->program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// Delete the shader as it is linked into our program now and no longer necessary
		glDeleteShader(shader);
	}
}

void Shader::use()
{
	glUseProgram(this->program);
}
