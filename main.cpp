#include <iostream>
#include "GameManager.h"
#include "Camera.h"
#include "filesystem.h"
#include"PlayerScript.h"
#include<vector>
#include <glm/gtc/type_ptr.hpp>



GameManager *GM=new GameManager();


int main() {


    GM->Init();


Script * player=new PlayerScript();

    Model *ourModel=new Model(FileSystem::getPath("objects/cyborg/cyborg.obj"));
    Model *ourModel2=new Model(FileSystem::getPath("objects/nanosuit/nanosuit.obj"));

    GM->AddModel(ourModel);
    GM->AddModel(ourModel2);


    // <-- Don't forget this one!
   // Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));





// Set the required callback functions
GM->gameModel[0]->AttachScript(player);
  GM->Start(); //call start in all models script component

    // Draw in wireframe
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(GM->GetWindow()))
    {
     GM->UpdateGameParameters();
        GM->Update();
        GM->Draw();
    }

    glfwTerminate();
    return 0;
}
