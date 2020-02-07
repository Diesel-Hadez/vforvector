#include "Shader.h"
#include <fstream>

namespace {
	std::string ReadFromFile(const std::string &filename) {
		std::string ret;
		std::ifstream file(filename);
		if (!file.is_open()) {
			throw std::runtime_error(std::string("Could not find file " + filename));
		}
		file.seekg(0, std::ios::end);
		ret.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		ret.assign(std::istreambuf_iterator<char>(file),
				std::istreambuf_iterator<char>());
		return ret;
	}

	GLuint CreateShader(const std::string &source, Shader::Type type) {
		GLuint shader;
		if (type == Shader::Type::Vertex)
			shader = glCreateShader(GL_VERTEX_SHADER);
		else
			shader = glCreateShader(GL_FRAGMENT_SHADER);
		const char * temp = source.c_str();
		glShaderSource(shader, 1, &temp, nullptr);
		glCompileShader(shader);

		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			throw std::runtime_error(std::string("Shader error: " + std::string(infoLog)));
		}
		return shader;
	}
}

void Shader::Use() noexcept{
	glUseProgram(m_ShaderProgram);
}

void Shader::Set(const std::string & name, bool value)
{
	GLint location = glGetUniformLocation(m_ShaderProgram , name.c_str());
	if (location == -1)
		throw std::runtime_error("ERROR::SHADER: BOOL UNIFORM " + name + " NOT FOUND!");
	glUniform1i(location, value);
}

void Shader::Set(const std::string & name, int value)
{
	GLint location = glGetUniformLocation(m_ShaderProgram , name.c_str());
	if (location == -1)
		throw std::runtime_error("ERROR::SHADER: INT UNIFORM " + name + " NOT FOUND!");
	glUniform1i(location, value);
}

void Shader::Set(const std::string & name, float value)
{
	GLint location = glGetUniformLocation(m_ShaderProgram , name.c_str());
	if (location == -1)
		throw std::runtime_error("ERROR::SHADER: FLOAT UNIFORM " + name + " NOT FOUND!");
	glUniform1f(location, value);
}

void Shader::Set(const std::string & name, glm::mat4 value)
{
	GLint location = glGetUniformLocation(m_ShaderProgram , name.c_str());
	if (location == -1)
		throw std::runtime_error("ERROR::SHADER: MAT4 UNIFORM " + name + " NOT FOUND!");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

}
void Shader::Set(const std::string & name, glm::vec4 value)
{
	GLint location = glGetUniformLocation(m_ShaderProgram , name.c_str());
	if (location == -1)
		throw std::runtime_error("ERROR::SHADER: VEC3 UNIFORM " + name + " NOT FOUND!");
	glUniform4fv(location, 1, glm::value_ptr(value));

}

void Shader::Set(const std::string & name, glm::vec3 value)
{
	GLint location = glGetUniformLocation(m_ShaderProgram , name.c_str());
	if (location == -1)
		throw std::runtime_error("ERROR::SHADER: VEC3 UNIFORM " + name + " NOT FOUND!");
	glUniform3fv(location, 1, glm::value_ptr(value));

}
void Shader::Set(const std::string & name, glm::vec2 value)
{
	GLint location = glGetUniformLocation(m_ShaderProgram , name.c_str());
	if (location == -1)
		throw std::runtime_error("ERROR::SHADER: VEC2 UNIFORM " + name + " NOT FOUND!");
	glUniform2fv(location, 1, glm::value_ptr(value));
}

Shader::Shader(const std::string &vertex_filename, const std::string &fragment_filename) {
	std::string vertexSource = ReadFromFile(vertex_filename);
	std::string fragmentSource = ReadFromFile(fragment_filename);
	GLuint vertexShader, fragmentShader;
	try { 
		vertexShader = CreateShader(vertexSource, Shader::Type::Vertex);
		fragmentShader = CreateShader(fragmentSource, Shader::Type::Fragment);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShader);
	glAttachShader(m_ShaderProgram, fragmentShader);
	glLinkProgram(m_ShaderProgram);

	try {
		GLint success;
		char infoLog[512];
		glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
			throw std::runtime_error(std::string("Shader Program error: " + std::string(infoLog) ));
		}
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



}

Shader::~Shader(){
    glDeleteProgram(m_ShaderProgram);
}
