#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Scene.h"
#include <memory>
#include "Shader.h"

class FPCamera;
class TextRenderer;
class GameScene: public Scene
{
	private:
        void DrawPoint(int x, int y, int z);
        void DrawLine(int startX, int startY, int startZ, int endX, int endY, int endZ);
		double m_DeltaTime;
        Shader m_Shader;
		glm::mat4 m_Projection;
        std::unique_ptr<TextRenderer> m_SomeText;
		std::unique_ptr<FPCamera> m_FPCamera;
	public:
		virtual void Update() override;
		virtual void Render() override;
		GameScene();
		~GameScene();
};

#endif
