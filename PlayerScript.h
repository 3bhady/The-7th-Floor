//
// Created by mohamed on 12/12/16.
//

#ifndef JUNG_PLAYERSCRIPT_H
#define JUNG_PLAYERSCRIPT_H
#include"Script.h"
#include"iostream"

class PlayerScript:public Script {

public:


    void Update(){
        if(IsKeyDown(GLFW_KEY_O))
        {
            model->IsAnimated=true;
        }
      if(IsKeyDown(GLFW_KEY_W))
        model->gameManager->camera->ProcessKeyboard(FORWARD, model->gameManager->deltaTime);
        if(IsKeyDown(GLFW_KEY_S))
            model->gameManager->camera->ProcessKeyboard(BACKWARD, model->gameManager->deltaTime);
        if(IsKeyDown(GLFW_KEY_A))
            model->gameManager->camera->ProcessKeyboard(LEFT, model->gameManager->deltaTime);
        if(IsKeyDown(GLFW_KEY_D))
            model->gameManager->camera->ProcessKeyboard(RIGHT,model->gameManager->deltaTime);
        if(IsKeyDown(GLFW_KEY_RIGHT))
        {
            vec3 pos=model->position;
            vec3 movTemp=-model->right*0.1f;
            model->SetPosition(vec3(model->position.x+movTemp.x,model->position.y+movTemp.y,model->position.z+movTemp.z));
        }
        if(IsKeyDown(GLFW_KEY_LEFT))
        {
            vec3 pos=model->position;
            vec3 movTemp=model->right*0.1f;
            model->SetPosition(vec3(model->position.x+movTemp.x,model->position.y+movTemp.y,model->position.z+movTemp.z));
        }
        if(IsKeyDown(GLFW_KEY_UP))
        {
            vec3 pos=model->position;
            vec3 movTemp=-model->direction*0.01f;
            model->SetPosition(vec3(model->position.x+movTemp.x,model->position.y+movTemp.y,model->position.z+movTemp.z));
        }
        if(IsKeyDown(GLFW_KEY_DOWN))
        {
            vec3 pos=model->position;
            vec3 movTemp=model->direction*0.01f;
            model->SetPosition(vec3(model->position.x+movTemp.x,model->position.y+movTemp.y,model->position.z+movTemp.z));
        }
        if(IsKeyDown(GLFW_KEY_Q))
        {
            model->Rotate(0,1,0,90*model->gameManager->deltaTime);
        }
        if(IsKeyDown(GLFW_KEY_E))
        {
            model->Rotate(0,1,0,-90*model->gameManager->deltaTime);
        }
        if(IsKeyDown(GLFW_KEY_F))
        {
            model->SetScaling(vec3(0.9f,0.9f,0.9f));
        }
        if(IsKeyDown(GLFW_KEY_G))
        {
            model->SetScaling(vec3(-0.9,-0.9,-0.9));
        }





    }
    void Start(){

        std::cout<<" hello it's me the script component Start!!!";
    }



};


#endif //JUNG_PLAYERSCRIPT_H
