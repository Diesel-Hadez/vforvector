//Largely thanks to learnopengl.com
#include "stdafx.h"
#include "TextRenderer.h"
#include "Shader.h"
#include "Game.h"

#include <ft2build.h>
#include FT_FREETYPE_H


void TextRenderer::RenderText(const std::string & text, GLfloat x, GLfloat y,  glm::vec3 colour, GLfloat scale)
{
	m_TextShader->Use();
	m_TextShader->Set<glm::vec3>("textColour", colour);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAOtext);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = m_Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;

		GLfloat vertices[6][4] = {
			{xpos, ypos+h,0.0,0.0},
			{xpos, ypos, 0.0,1.0},
			{xpos+w,ypos, 1.0,1.0},

			{xpos,ypos+h,0.0,0.0},
			{xpos+w, ypos, 1.0,1.0},
			{xpos+w,ypos+h,1.0,0.0}
		};
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, VBOtext);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

TextRenderer::TextRenderer()
{
	m_TextShader = std::make_unique<Shader>("../assets/TextShader.vs", "../assets/TextShader.fs");
	m_TextShader->Use();
	m_TextShader->Set<glm::mat4>("projection", glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), 0.0f, static_cast<float>(WINDOW_HEIGHT)));
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cerr << "ERROR::FREETYPE: Could not initialize FreeType library!\n";
	}
	FT_Face face;
	if (FT_New_Face(ft, "../assets/Font/NotoMono-Regular.ttf", 0, &face))
		std::cerr << "ERROR::FREETYPE: Failed to load font Font/NotoMono-Regular.ttf\n";
	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cerr << "ERROR::FREETYPE: Failed to load Glyph " << std::to_string(c) << "\n";
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width,face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		m_Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenBuffers(1, &VBOtext);
	glGenVertexArrays(1, &VAOtext);

	glBindVertexArray(VAOtext);

	glBindBuffer(GL_ARRAY_BUFFER, VBOtext);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	m_TextShader->Use();

}


TextRenderer::~TextRenderer()
{
}
 
