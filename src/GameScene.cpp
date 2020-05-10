#include "stdafx.h"
#include "GameScene.h"
#include "Shader.h"
#include "FPCamera.h"
#include "Game.h"
#include "TextRenderer.h"
#include <glm/glm.hpp>
#include "Vector.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

static GameScene *	curGameScene	= nullptr;
static double currentFrame	= 0;
static double lastFrame		= 0;
constexpr double ZOOM		= 45.0;
static unsigned int VAO=0;
std::mt19937 pr_engine{static_cast<std::mt19937::result_type>(std::time(nullptr)) };
static Vector qvec1;
static Vector qvec2;
static Coordinate qcoord1;
static Coordinate qcoord2;
static std::string curQuestion = "";
static std::string curAnswer = "";
static std::string correctAnswer = "";
static std::string timer = "";

std::map<int, bool> is_pressed;

static bool bothvecs = false;
static Coordinate startPoint;
static glm::mat4 twodprojection;
static double startTime=0;

static std::string double_to_str(double number) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << number;
    return ss.str();   
}

static void CheckAnswer() {
    curAnswer.erase(std::remove (curAnswer.begin(), curAnswer.end(), ' '), curAnswer.end());   
    if (curAnswer == correctAnswer) {
        curAnswer = "Correct! Next Question? (Y)";
    }
    else{
        curAnswer = "Correct! Next Question? (Y)";
    }
}

static void UpdateQuestion(){
    startTime = glfwGetTime();
    static std::uniform_int_distribution<int> which_question(0,1);
    static std::uniform_int_distribution<int> range_10(0,10);
    constexpr int ANGLE_QUESTION = 0;
    constexpr int UNITVECTOR_QUESTION = 1;
    int random_question = which_question(pr_engine); 
    
    startPoint.X = 0.0;
    startPoint.Y = 0.0;
    startPoint.Z = 0.0;
    if (random_question == ANGLE_QUESTION){
        bothvecs = true;
        qvec1.X = static_cast<double>(range_10(pr_engine));
        qvec1.Y = static_cast<double>(range_10(pr_engine));
        qvec1.Z = static_cast<double>(range_10(pr_engine));
        
        qvec2.X = static_cast<double>(range_10(pr_engine));
        qvec2.Y = static_cast<double>(range_10(pr_engine));
        qvec2.Z = static_cast<double>(range_10(pr_engine));
        
        curQuestion = "What is the angle between vectors " + double_to_str(qvec1.X) + "i + " +
        double_to_str(qvec1.Y) + "j + " + double_to_str(qvec1.Z) + "k and " + 
        double_to_str(qvec2.X) + "i + "+ double_to_str(qvec2.Y) + "j + " +double_to_str(qvec2.Z) + "k";
        correctAnswer = double_to_str(Vector::Angle(qvec1, qvec2));
    }
    else if (random_question == UNITVECTOR_QUESTION) {
        bothvecs = false;
        qvec1.X = static_cast<double>(range_10(pr_engine));
        qvec1.Y = static_cast<double>(range_10(pr_engine));
        qvec1.Z = static_cast<double>(range_10(pr_engine));
        
        curQuestion = "What is the Unit vector of " + double_to_str(qvec1.X) + "i + " +
        double_to_str(qvec1.Y) + "j + " + double_to_str(qvec1.Z) + "k?";
        Vector correctVec = qvec1.UnitVector();
        correctAnswer = double_to_str(correctVec.X) + "I+" + double_to_str(correctVec.Y) + "J+" +double_to_str(correctVec.Z) + "K";
    }
}

void GameScene::Update()
{
	currentFrame   = glfwGetTime();
	m_DeltaTime    = currentFrame - lastFrame;
	lastFrame      = currentFrame;

    if (curAnswer != correctAnswer) {
            timer = double_to_str((currentFrame-startTime)) + "s";
    }
	if (glfwGetKey(Game::m_Window, GLFW_KEY_W) == GLFW_PRESS)
		m_FPCamera->ProcessKeyboard(FPCamera::Movement::FORWARD, m_DeltaTime);
	if (glfwGetKey(Game::m_Window, GLFW_KEY_S) == GLFW_PRESS)
		m_FPCamera->ProcessKeyboard(FPCamera::Movement::BACKWARD, m_DeltaTime);
	if (glfwGetKey(Game::m_Window, GLFW_KEY_A) == GLFW_PRESS)
		m_FPCamera->ProcessKeyboard(FPCamera::Movement::LEFT, m_DeltaTime);
	if (glfwGetKey(Game::m_Window, GLFW_KEY_D) == GLFW_PRESS)
		m_FPCamera->ProcessKeyboard(FPCamera::Movement::RIGHT, m_DeltaTime);
	if (glfwGetKey(Game::m_Window, GLFW_KEY_Q) == GLFW_PRESS)
		m_FPCamera->ProcessKeyboard(FPCamera::Movement::UP, m_DeltaTime);
	if (glfwGetKey(Game::m_Window, GLFW_KEY_E) == GLFW_PRESS)
		m_FPCamera->ProcessKeyboard(FPCamera::Movement::DOWN, m_DeltaTime);
	if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        is_pressed[GLFW_KEY_ESCAPE] = true;
    if (glfwGetKey(Game::m_Window, GLFW_KEY_I) == GLFW_PRESS)
        is_pressed[GLFW_KEY_I] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_J) == GLFW_PRESS)
        is_pressed[GLFW_KEY_J] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_K) == GLFW_PRESS)
        is_pressed[GLFW_KEY_K] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        is_pressed[GLFW_KEY_SPACE] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_EQUAL) == GLFW_PRESS)
        is_pressed[GLFW_KEY_EQUAL] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_MINUS) == GLFW_PRESS)
        is_pressed[GLFW_KEY_MINUS] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
        is_pressed[GLFW_KEY_BACKSPACE] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_0) == GLFW_PRESS)
        is_pressed[GLFW_KEY_0] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_1) == GLFW_PRESS)
        is_pressed[GLFW_KEY_1] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_2) == GLFW_PRESS)
        is_pressed[GLFW_KEY_2] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_3) == GLFW_PRESS)
        is_pressed[GLFW_KEY_3] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_4) == GLFW_PRESS)
        is_pressed[GLFW_KEY_4] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_5) == GLFW_PRESS)
        is_pressed[GLFW_KEY_5] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_6) == GLFW_PRESS)
        is_pressed[GLFW_KEY_6] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_7) == GLFW_PRESS)
        is_pressed[GLFW_KEY_7] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_8) == GLFW_PRESS)
        is_pressed[GLFW_KEY_8] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_9) == GLFW_PRESS)
        is_pressed[GLFW_KEY_9] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_ENTER) == GLFW_PRESS)
        is_pressed[GLFW_KEY_ENTER] = true;
	if (glfwGetKey(Game::m_Window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        is_pressed[GLFW_KEY_PERIOD] = true;

    if (glfwGetKey(Game::m_Window, GLFW_KEY_ENTER) == GLFW_RELEASE && is_pressed[GLFW_KEY_ENTER]){
        CheckAnswer();
        is_pressed[GLFW_KEY_ENTER] = false;
    }
	
    if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && is_pressed[GLFW_KEY_ESCAPE]){
        m_End = true;
    }
    
    if (glfwGetKey(Game::m_Window, GLFW_KEY_I) == GLFW_RELEASE && is_pressed[GLFW_KEY_I]){
        curAnswer += "I";
        is_pressed[GLFW_KEY_I] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_PERIOD) == GLFW_RELEASE && is_pressed[GLFW_KEY_PERIOD]){
        curAnswer += ".";
        is_pressed[GLFW_KEY_PERIOD] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_J) == GLFW_RELEASE && is_pressed[GLFW_KEY_J]){
        curAnswer += "J";
        is_pressed[GLFW_KEY_J] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_K) == GLFW_RELEASE && is_pressed[GLFW_KEY_K]){
        curAnswer += "K";
        is_pressed[GLFW_KEY_K] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_SPACE) == GLFW_RELEASE && is_pressed[GLFW_KEY_SPACE]){
        curAnswer += " ";
        is_pressed[GLFW_KEY_SPACE] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_EQUAL) == GLFW_RELEASE && is_pressed[GLFW_KEY_EQUAL]){
        curAnswer += "+";
        is_pressed[GLFW_KEY_EQUAL] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_MINUS) == GLFW_RELEASE && is_pressed[GLFW_KEY_MINUS]){
        curAnswer += "-";
        is_pressed[GLFW_KEY_MINUS] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_0) == GLFW_RELEASE && is_pressed[GLFW_KEY_0]){
        curAnswer += "0";
        is_pressed[GLFW_KEY_0] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_1) == GLFW_RELEASE && is_pressed[GLFW_KEY_1]){
        curAnswer += "1";
        is_pressed[GLFW_KEY_1] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_2) == GLFW_RELEASE && is_pressed[GLFW_KEY_2]){
        curAnswer += "2";
        is_pressed[GLFW_KEY_2] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_3) == GLFW_RELEASE && is_pressed[GLFW_KEY_3]){
        curAnswer += "3";
        is_pressed[GLFW_KEY_3] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_4) == GLFW_RELEASE && is_pressed[GLFW_KEY_4]){
        curAnswer += "4";
        is_pressed[GLFW_KEY_4] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_5) == GLFW_RELEASE && is_pressed[GLFW_KEY_5]){
        curAnswer += "5";
        is_pressed[GLFW_KEY_5] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_6) == GLFW_RELEASE && is_pressed[GLFW_KEY_6]){
        curAnswer += "6";
        is_pressed[GLFW_KEY_6] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_7) == GLFW_RELEASE && is_pressed[GLFW_KEY_7]){
        curAnswer += "7";
        is_pressed[GLFW_KEY_7] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_8) == GLFW_RELEASE && is_pressed[GLFW_KEY_8]){
        curAnswer += "8";
        is_pressed[GLFW_KEY_8] = false;
    }
    
    if (glfwGetKey(Game::m_Window, GLFW_KEY_9) == GLFW_RELEASE && is_pressed[GLFW_KEY_9]){
        curAnswer += "9";
        is_pressed[GLFW_KEY_9] = false;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_BACKSPACE) == GLFW_RELEASE &&
        (curAnswer.length() > 0)  && is_pressed[GLFW_KEY_BACKSPACE]) {
        curAnswer.pop_back();
        is_pressed[GLFW_KEY_BACKSPACE] = false;
    }
    
        m_Projection = glm::perspective(static_cast<float>(glm::radians(ZOOM)), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 100.0f);

}

void GameScene::DrawLine(int startX, int startY, int startZ, int endX, int endY, int endZ){
    glm::mat4 model2 (1.f);
    Vector test;
    test.X = endX-startX;
    test.X = endY-startY;
    test.X = endZ-startZ;
    //Line test
    m_Shader.Set<glm::vec4>("color", glm::vec4(0.5f, 0.0f, 0.5f, 1.0f));
    model2 = glm::translate(model2, glm::vec3(startX, startY, startZ));
    model2 = glm::rotate(model2, static_cast<float>(std::atan(test.Y/test.X)), glm::vec3(0.f,0.f,1.f));    
    model2 = glm::rotate(model2, static_cast<float>(std::atan(test.Z/test.X)), glm::vec3(0.0f,1.0f,0.0f));
  
    model2 = glm::scale(model2, glm::vec3(test.Magnitude(), 0.1f, 0.1f));
    model2 = glm::translate(model2, glm::vec3(0.5, 0.5, 0.5));
    m_Shader.Set<glm::mat4>("model", model2);
    glDrawArrays(GL_TRIANGLES, 0, 36);   
}

void GameScene::DrawPoint(int x, int y, int z) {
    glm::mat4 model2 (1.f);
    Vector test;
    test.X = 1/std::sqrt(200);
    test.Y = 1/std::sqrt(200);
    test.Z = 1/std::sqrt(200);
    //Line test
    m_Shader.Set<glm::vec4>("color", glm::vec4(0.8f, 0.0f, 0.0f, 1.0f));
    model2 = glm::translate(model2, glm::vec3(x, y, z));
    model2 = glm::rotate(model2, static_cast<float>(std::atan(test.Y/test.X)), glm::vec3(0.f,0.f,1.f));    
    model2 = glm::rotate(model2, static_cast<float>(std::atan(test.Z/test.X)), glm::vec3(0.0f,1.0f,0.0f));
  
    model2 = glm::scale(model2, glm::vec3(test.Magnitude(), 0.1f, 0.1f));
    model2 = glm::translate(model2, glm::vec3(0.5, 0.5, 0.5));
    m_Shader.Set<glm::mat4>("model", model2);
    glDrawArrays(GL_TRIANGLES, 0, 36);   
}

void GameScene::Render()
{
	glm::mat4 model(1.0f);
    glm::mat4 model2(model);
    glm::mat4 model3(model);
	glm::mat4 view(1.0f);
	view = m_FPCamera->GetViewMatrix();
	glClearColor(0.f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_Shader.Use();
    m_Shader.Set<glm::mat4>("projection", m_Projection);
    m_Shader.Set<glm::mat4>("model", model);
    m_Shader.Set<glm::mat4>("view", view);
    
    
    glBindVertexArray(VAO);
     // Grid color
    m_Shader.Set<glm::vec4>("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    //The "grid"
    for (std::int32_t x = -15; x < 15; x++ ) {
        
        //Y Axis (Up)
        m_Shader.Set<glm::mat4>("model", glm::scale(glm::translate(model,glm::vec3(static_cast<float>(x),0.0f, 0.0f)), 
                                                    glm::vec3(0.1f, 30.0f, 0.1f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //Z Axis 
        m_Shader.Set<glm::mat4>("model", glm::scale(glm::translate(model,glm::vec3(0.0f,static_cast<float>(x), 0.0f)), 
                                                    glm::vec3(0.1f, 0.1f, 30.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //X Axis 
        m_Shader.Set<glm::mat4>("model", glm::scale(glm::translate(model,glm::vec3(0.0f,0.0f, static_cast<float>(x))), 
                                                    glm::vec3(30.0f, 0.1f, 0.1f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
    }
    
    DrawPoint(-1, 2, 5);
    DrawPoint(2, -2, 11);
    DrawPoint(1, 1, 1);
    
    DrawLine(-1,2,5,1,1,1);
     int l = 10;
    Vector ac;
    ac.X = 1-(-1);
    ac.Y = 1-2;
    ac.Z = 1-5;
    DrawLine(2,-2,11,l*(ac.X), l*(ac.Y), l*(ac.Z));
    
    /*
    Vector test = qvec1;
    //Line test
    m_Shader.Set<glm::vec4>("color", glm::vec4(0.5f, 0.0f, 0.5f, 1.0f));
    model2 = glm::translate(model2, glm::vec3(1, 1, 1));
    model2 = glm::rotate(model2, static_cast<float>(std::atan(test.Y/test.X)), glm::vec3(0.f,0.f,1.f));    
    model2 = glm::rotate(model2, static_cast<float>(std::atan(test.Z/test.X)), glm::vec3(0.0f,1.0f,0.0f));
  
    model2 = glm::scale(model2, glm::vec3(test.Magnitude(), 0.1f, 0.1f));
    model2 = glm::translate(model2, glm::vec3(0.5, 0.5, 0.5));
    m_Shader.Set<glm::mat4>("model", model2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    if (bothvecs){
        test = qvec2;
         m_Shader.Set<glm::vec3>("color", glm::vec3(0.5f, 0.0f, 0.5f));
        model3 = glm::rotate(model3, static_cast<float>(std::atan(test.Y/test.X)), glm::vec3(0.f,0.f,1.f));    
        model3 = glm::rotate(model3, static_cast<float>(std::atan(test.Z/test.X)), glm::vec3(0.0f,1.0f,0.0f));
    
        model3 = glm::scale(model3, glm::vec3(test.Magnitude(), 0.1f, 0.1f));
        model3 = glm::translate(model3, glm::vec3(0.5, 0.5, 0.5));
        m_Shader.Set<glm::mat4>("model", model3);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
      */  
	glClear(GL_DEPTH_BUFFER_BIT);
    m_Shader.Set<glm::vec4>("color", glm::vec4(0.0f, 0.0f, 0.0f, 0.7f));
    m_Shader.Set<glm::mat4>("view", glm::mat4(1.f));
    m_Shader.Set<glm::mat4>("projection", twodprojection);
    glm::mat4 model4 (1.f);
    model4 = glm::translate(model4,glm::vec3(static_cast<float>(WINDOW_WIDTH)/2.f, 100.0f, 1.0f));
    model4 = glm::scale(model4,glm::vec3(WINDOW_WIDTH,200.f,1.f));
    m_Shader.Set<glm::mat4>("model", model4);
    glDrawArrays(GL_TRIANGLES, 0, 36);
	glClear(GL_DEPTH_BUFFER_BIT);
    
    m_SomeText->RenderText(curQuestion,0.0f,static_cast<float>(WINDOW_HEIGHT)-20.0f, glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
    m_SomeText->RenderText(curAnswer,0.0f,static_cast<float>(WINDOW_HEIGHT)-40.0f, glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);    m_SomeText->RenderText("Timer: " + timer,static_cast<float>(WINDOW_WIDTH)-200.f,static_cast<float>(WINDOW_HEIGHT)-40.0f, glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
   
    m_SomeText->RenderText("(" + std::to_string(m_FPCamera->Position.x) + ", " + 
                                 std::to_string(m_FPCamera->Position.y) + ", " +
                                  std::to_string(m_FPCamera->Position.z) + ")",0.0f,0.0f);

}

GameScene::GameScene() : m_DeltaTime(0.0f), m_Shader("../assets/Default.vert","../assets/Default.frag")
{
    twodprojection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
    UpdateQuestion();
    for (int i=32;i>90;i++)
        is_pressed.insert({i, false});
	m_SceneName		 = "GameScene";
	m_FPCamera		= std::make_unique<FPCamera>(glm::vec3(0.0f, 0.0f, 3.0f));
    m_SomeText      = std::make_unique<TextRenderer>();
    
	//Dirty Hack for callbacks
	curGameScene = this;

	glfwSetInputMode(Game::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(Game::m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		static bool firstMouse = true;
		static double lastX = static_cast<double>(WINDOW_WIDTH / 2.f), lastY = static_cast<double>(WINDOW_HEIGHT / 2.f);
		if (firstMouse)
		{
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
		}
		double xOffset = xPos - lastX;
		double yOffset = lastY - yPos;
		lastX = xPos;
		lastY = yPos;
		curGameScene->m_FPCamera->ProcessMouseMovement(xOffset, yOffset);
	});
	glfwSetScrollCallback(Game::m_Window, [](GLFWwindow * window, double xOffset, double yOffset) {
		curGameScene->m_FPCamera->ProcessMouseScroll(yOffset);
	});
    
     float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f,
    };

    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
}


GameScene::~GameScene()
{
    //Reset Callback
    glfwSetCursorPosCallback(Game::m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{});
}

