#ifndef HIGHSCORESCENE_H
#define HIGHSCORESCENE_H
#include "Scene.h"
#include <memory>
#include "Shader.h"

class TextRenderer;
class HighscoreScene: public Scene
{
	private:
		double m_DeltaTime;
        Shader m_Shader;
		glm::mat4 m_Projection;
        std::unique_ptr<TextRenderer> m_SomeText;
	public:
		virtual void Update() override;
		virtual void Render() override;
		HighscoreScene();
		~HighscoreScene();
};

#endif

