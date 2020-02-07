#ifndef SHADER_H
#define SHADER_H
#include "stdafx.h"

class Shader {
	private:
		GLuint m_ShaderProgram;
		void Set(const std::string &name, bool value);
		void Set(const std::string &name, int value);
		void Set(const std::string &name, float value);
		void Set(const std::string &name, glm::mat4 value);
		void Set(const std::string &name, glm::vec3 value);
		void Set(const std::string &name, glm::vec2 value);
		void Set(const std::string &name, glm::vec4 value);

	public:
		enum class Type {
			Vertex,
			Fragment
		};
		template <typename T>
		void Set(const std::string &name, const T &a);

		void Use() noexcept;
		Shader(const std::string &vertex_file, const std::string &fragment_file);
		~Shader();
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

};

template<typename T>
inline void Shader::Set(const std::string &name, const T & a)
{
	try
	{
		this->Set(name, a);
	}
	catch (const std::exception &e)
	{
		std::cerr << "ERROR::SHADER: " << e.what() << "\n";
	}
}


#endif
