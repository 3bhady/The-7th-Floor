



#include <iostream>
#include "GameManager.h"
#include "Camera.h"

#include"PlayerScript.h"
#include "Model2D.h"

#include<vector>
#include <glm/gtc/type_ptr.hpp>
GameManager *GM=new GameManager();
//testing section shaders

const GLchar* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

//shadersss
int main() {
    GM->Init();
    Script * player=new PlayerScript();
   // Model *ourModel=new Model(FileSystem::getPath("objects/cyborg/test.obj"));
   // GM->AddModel(ourModel);
   GM->Create_Object("nanosuit");
    GM->Create_Object("cyborg");
    GM->Create_Object("scene");
    GM->Create_Object("test");
    GM->CreateObject2D("cursor");

// Set the required callback functions
GM->gameModel[1]->AttachScript(player);
   GM->gameModel[0]->Trigger(true);
    GM->gameModel[1]->Trigger(true);
  GM->Start(); //call start in all models script component
    Model2D *model2D = new Model2D(std::__cxx11::string());
    while(!glfwWindowShouldClose(GM->GetWindow()))
    {
    GM->UpdateGameParameters();
        GM->Check_Collision();
        GM->Update();
        glClearColor(0.5f, 0.05f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      GM->Draw();

     glfwSwapBuffers(GM->GetWindow());

    }
    glfwTerminate();
    return 0;
}
//
