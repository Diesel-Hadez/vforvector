#ifndef GAME_H
#define GAME_H
#include "stdafx.h"
#include <vector>
#include <memory>
class Scene;
class Game
{
public:
	static GLFWwindow * m_Window;
private:
	Game();
	void InitOpenGL();
#ifdef __EMSCRIPTEN__
public:
#endif
    void loop();
public:
	std::vector<std::unique_ptr<Scene>> m_Scenes;
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
	static Game& GetInstance() 
	{
		static Game instance;
		return instance;
	}
	void Run();
	~Game();
};

#endif

