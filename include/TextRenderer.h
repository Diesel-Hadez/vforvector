#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
#include "stdafx.h"
#include <memory>
#include <map>

class Shader;
class TextRenderer
{
private:
	struct Character {
		GLuint TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint Advance;
	};
	std::map<GLchar, Character> m_Characters;
	unsigned VAOtext, VBOtext;
	unsigned int textureText;
	std::unique_ptr<Shader> m_TextShader;

public:
	void RenderText(const std::string &text, GLfloat x, GLfloat y, glm::vec3 colour=glm::vec3(1.f,0.0f,0.0f), GLfloat scale=1.f);
	TextRenderer();
	~TextRenderer();
};

#endif

 
