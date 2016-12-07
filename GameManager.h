#pragma once
#include <vector>
#include <string>
#include "Model.h"
#include <GLFW/glfw3.h>


class Game_Manager {
private:
    GLFWwindow * window;
    std::vector<Model*>Hierarchy; //list of all the objects in the game
public:
    void Init();
    void Start();
    void Create_Object(std::string tag);
    void Update();
    void Check_Collision();
    void LoadScene();
    void Destroy_Object();
    GLFWwindow* GetWindow();
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


    //shouldn't be public
    Shader* shader;

};

