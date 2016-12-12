#pragma once
#ifndef game
#define game
#include <vector>
#include <string>
#include "Model.h"
#include <GLFW/glfw3.h>
#include "Input.h"
#include "Camera.h"
#endif



class GameManager {
private:
    GLFWwindow * window;
  //  std::vector<Model*>GameModel; //list of all the objects in the game
  GLfloat currentFrame ;//for deltatime

    GLfloat lastFrame;//last frame for deltatime
    GLuint screenWidth = 800, screenHeight = 600;
public:
    Camera* camera ;
     Input *  input;
    GLfloat deltaTime ;//last frame for delta time
    GameManager();
    void Init();
    void Start();
    void Create_Object(std::string tag);
    void Update();
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

    void UpdateGameParameters();
    //shouldn't be public
    Shader* shader;

};

