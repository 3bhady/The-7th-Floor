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
    void Do_Movement()
    {
        // Camera controls
        if(input->IsKeyDown(GLFW_KEY_W))
         cout<<"W is down "<<endl;
    }

    void UpdateGameParameters();//updating parameters like deltatime
    void Update();
    void Start();
    void Draw();
    void AddModel(Model*& m);

    //shouldn't be public
    Shader* shader;

};

