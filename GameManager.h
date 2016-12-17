#pragma once
#ifndef game
#define game
#include <vector>
#include <string>
#include "Model.h"
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Input.h"
#include"Model.h"
#include "Model2D.h"

#endif



class GameManager {
private:
    GLFWwindow * window;

  GLfloat currentFrame ;//for deltatime

    GLfloat lastFrame;//last frame for deltatime
    GLuint screenWidth = 1024, screenHeight = 768;
   string  windowName;
public:
    std::vector<Model*>gameModel; //list of all the objects in the game
    std::vector<Model2D*>gameModel2D;
    Camera* camera ;
     Input *  input;
    GLfloat deltaTime ;//last frame for delta time
    GameManager();
    void Init(GLuint screenWidth = 1024, GLuint screenHeight = 768,std::string windowName="7th-Floor");

    void Create_Object(std::string tag);

    void Check_Collision();
    void LoadScene();
    void Destroy_Object();
    GLFWwindow* GetWindow();
    void UpdateDeltaTime();//updating deltatime
    void UpdatePollEvents();

    void UpdateGameParameters();//updating parameters like deltatime
    void Update();
    void Start();
    void Draw();
    void AddModel(Model*& m);
    void AddModel2D(Model2D*& m);

    //shouldn't be public
    Shader* shader;
    Shader* shader2D;

  Model* Inistatiate(string tag);
    Model* GetModelByTag(string tag);
    void CreateObject2D(string tag);
};

