
#include "stdafx.h"
#include "HighscoreScene.h"
#include "Shader.h"
#include "Game.h"
#include "TextRenderer.h"
#include "GameScene.h"
#include <glm/glm.hpp>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "Vector.h"
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static double currentFrame	= 0;
static double lastFrame		= 0;
static bool upPressed=false;
static bool downPressed=false;
static bool enterPressed=false;
static bool escPressed=false;

static int curOption = 0;
static std::vector<float> vertices;
static unsigned int VAO;

static unsigned int textureID;
static bool viewHigh = false;

void HighscoreScene::Update()
{
	currentFrame 	= glfwGetTime();
	m_DeltaTime	= currentFrame - lastFrame;
	lastFrame	= currentFrame;

	if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        escPressed = true;
	}
	if (glfwGetKey(Game::m_Window, GLFW_KEY_ENTER) == GLFW_PRESS){
        enterPressed = true;
    }
	if (glfwGetKey(Game::m_Window, GLFW_KEY_UP) == GLFW_PRESS){
        upPressed = true;
    }

	if (glfwGetKey(Game::m_Window, GLFW_KEY_DOWN) == GLFW_PRESS){
        downPressed = true;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && escPressed){
        escPressed = false;
        if (viewHigh)
            viewHigh = false;
        else
            m_End = true;
    }

    if (glfwGetKey(Game::m_Window, GLFW_KEY_ENTER) == GLFW_RELEASE && enterPressed){
        enterPressed = false;
        if (curOption == 0)
            Game::GetInstance().m_Scenes.emplace_back(std::move(std::make_unique<GameScene>()));
        else if (curOption == 1)
            viewHigh = true;
        else
            m_End = true;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_UP) == GLFW_RELEASE && upPressed){
        upPressed = false;
        if (curOption > 0)
            curOption--;
    }
    if (glfwGetKey(Game::m_Window, GLFW_KEY_DOWN) == GLFW_RELEASE && downPressed){
        downPressed = false;
        if (curOption < 2)
            curOption++;
    }
	
  
}

void HighscoreScene::Render()
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glm::vec3 selectedColor = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 nonSelectedColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 playColor, highScoreColor, quitColor;
    playColor = nonSelectedColor;
    highScoreColor = nonSelectedColor;
    quitColor = nonSelectedColor;
    if (curOption == 0){
        playColor = selectedColor;
    }
    else if (curOption == 1){
        highScoreColor= selectedColor;
    }
    else{
        quitColor = selectedColor;
    }
    glm::mat4 model(1.0f);
    //model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    model = glm::translate(model, glm::vec3(0.00f,0.00f,-80.00f));  
    model = glm::rotate(model, static_cast<float>(glm::radians(90.f)), glm::vec3(1.0f,1.0f,1.0f));
   
  //  model = glm::rotate(model, static_cast<float>(glm::radians(180.f)), glm::vec3(1.0f,0.0f,0.0f));
   // model = glm::rotate(model, static_cast<float>(glm::radians(90.f)), glm::vec3(1.0f,0.0f,0.0f));
    //model = glm::rotate(model, static_cast<float>(std::sin(glfwGetTime())), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 view(1.0f);
    m_Shader.Use();
    m_Shader.Set<glm::mat4>("projection", glm::perspective(static_cast<float>(glm::radians(45.0f)), static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 0.1f, 200.0f));
    m_Shader.Set<glm::mat4>("model", model);
    m_Shader.Set<glm::mat4>("view", view);
    m_Shader.Set<int>("texture1", 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    m_Shader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/5); 
    if (viewHigh){
                m_SomeText->RenderText("Highscore",0.0f,static_cast<float>(WINDOW_HEIGHT)-30.0f, nonSelectedColor , 0.7f);        
        //TO-DO, pls. I need sleep
        m_SomeText->RenderText("12/2/5 - 2:03 3 Question(s)",0.0f,static_cast<float>(WINDOW_HEIGHT)-70.0f, playColor , 0.5f);
        m_SomeText->RenderText("12/2/5 - 8:03 4 Question(s)",0.0f,static_cast<float>(WINDOW_HEIGHT)-100.0f, highScoreColor , 0.5f);
        m_SomeText->RenderText("12/2/5 - 5:03 1 Question(s)",0.0f,static_cast<float>(WINDOW_HEIGHT)-130.0f, quitColor, 0.5f);

    }
    else{
        m_SomeText->RenderText("V is for Vector",0.0f,static_cast<float>(WINDOW_HEIGHT)-30.0f, nonSelectedColor , 0.7f);        
        m_SomeText->RenderText("Play",0.0f,static_cast<float>(WINDOW_HEIGHT)-70.0f, playColor , 0.5f);
        m_SomeText->RenderText("Highscore",0.0f,static_cast<float>(WINDOW_HEIGHT)-100.0f, highScoreColor , 0.5f);
        m_SomeText->RenderText("Quit",0.0f,static_cast<float>(WINDOW_HEIGHT)-130.0f, quitColor, 0.5f);
    }
}

struct FaceAccess {
    int V1;
    int V2;
    int V3;
    int T1;
    int T2;
    int T3;
    FaceAccess(){}
};

HighscoreScene::HighscoreScene() : m_DeltaTime(0.0f), m_Shader("../assets/LogoShader.vs","../assets/LogoShader.fs")
{
    m_Projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);

    m_SceneName		 = "HighscoreScene";
	m_SomeText      = std::make_unique<TextRenderer>();
    
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    std::ifstream is("../assets/3dmodel/logo.obj");
    std::vector<Coordinate> access_vertices;
    std::vector<Coordinate> access_texture;
    std::vector<FaceAccess> access_face;
    for (std::string str;std::getline(is, str);) {
        std::vector<std::string> cur;
        std::istringstream iss(str);
        for (std::string s;iss >> s;) {
         cur.emplace_back(s);   
        }
        if (cur[0][0] == 'f'){
         FaceAccess a; 
             std::vector<int> stuff;
         for (int abc=1;abc<=3;abc++){
         std::istringstream iss2(cur[abc]);
         for (std::string line; std::getline(iss2, line); ) {
         std::istringstream iss3(line); 
            std::string vert, text;
            std::getline(iss3,vert,'/');
            std::getline(iss3,text,'/');
            stuff.emplace_back(std::atoi(vert.c_str()));
            stuff.emplace_back(std::atoi(text.c_str()));
    }
         }
            a.V1 = stuff[0];
            a.T1 = stuff[1];
            a.V2 = stuff[2];
            a.T2 = stuff[3];
            a.V3 = stuff[4];
            a.T3 = stuff[5];
            
            access_face.emplace_back(a);
        }
        if (cur[0][0] == 'v' && 
            (cur[0].length() == 1))
            access_vertices.emplace_back(
                Coordinate(std::atof(cur[1].c_str()),
                           std::atof(cur[2].c_str()),
                           std::atof(cur[3].c_str())));
        if (cur[0][0] == 'v' && 
            (cur[0].length() == 2))
            access_texture.emplace_back(
                Coordinate(std::atof(cur[1].c_str()),
                           std::atof(cur[2].c_str()),
                           0.0));
    }
    
    for (std::size_t i=0;i<access_face.size();i++) {
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V1)-1].X);   
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V1)-1].Y);   
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V1)-1].Z);  
     vertices.emplace_back(access_texture[static_cast<int>(access_face[i].T1)-1].X*-1);  
     vertices.emplace_back(access_texture[static_cast<int>(access_face[i].T1)-1].Y);
     
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V2)-1].X);   
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V2)-1].Y);   
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V2)-1].Z);  
     vertices.emplace_back(access_texture[static_cast<int>(access_face[i].T2)-1].X*-1);  
     vertices.emplace_back(access_texture[static_cast<int>(access_face[i].T2)-1].Y);
     
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V3)-1].X);   
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V3)-1].Y);   
     vertices.emplace_back(access_vertices[static_cast<int>(access_face[i].V3)-1].Z);  
     vertices.emplace_back(access_texture[static_cast<int>(access_face[i].T3)-1].X*-1);  
     vertices.emplace_back(access_texture[static_cast<int>(access_face[i].T3)-1].Y);
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    
    stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load("../assets/3dmodel/Yes.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}


HighscoreScene::~HighscoreScene()
{
}

