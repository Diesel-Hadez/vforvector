#include "stdafx.h"
#include "Game.h"
#include "HighscoreScene.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
static void main_loop() { Game::GetInstance().loop();}
#endif

GLFWwindow * Game::m_Window = nullptr;

void Game::loop(){
    try
		{
			m_Scenes.back()->Update();
			m_Scenes.back()->Render();
		}
		catch (const std::exception &e)
		{
			std::cerr << "ERROR IN SCENE: " << m_Scenes.back()->m_SceneName << ": " << e.what() << "\nReverting to previous scene...\n";
			m_Scenes.pop_back();
			return;
		}
		catch (...)
		{
			std::cerr << "ERROR IN SCENE: " << m_Scenes.back()->m_SceneName << ": UNKNOWN ERROR\nReverting to previous scene...\n";
			m_Scenes.pop_back();
			return;
		}
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
#ifdef __EMSCRIPTEN__        
        if (m_Scenes.back()->m_End && m_Scenes.size() != 1)
            m_Scenes.pop_back();
#else
        if (m_Scenes.back()->m_End)
            m_Scenes.pop_back();
#endif
}

void Game::InitOpenGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#endif	
    m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "VisForVector", NULL, NULL);
	if (m_Window== NULL)
	{
		throw std::runtime_error("FATAL ERROR: Failed to create GLFW window");
	}
	glfwMakeContextCurrent(m_Window);
#ifndef __EMSCRIPTEN__
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		throw std::runtime_error("FATAL ERROR: Failed to initialize GLAD");
	}
#endif
	glClearDepth(static_cast<GLdouble>(1.0f));
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow * window, int width, int height) {glViewport(0, 0, width, height); });
}

void Game::Run()
{
    InitOpenGL();
	m_Scenes.emplace_back(std::make_unique<HighscoreScene>());
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop, 0, true);
#else
	while ((m_Scenes.size() > 0) && (!glfwWindowShouldClose(m_Window)))
	{
		this->loop();
	}
#endif
	glfwTerminate();
}

Game::Game()
{
}


Game::~Game()
{
}
