//
// Created by mohamed on 12/12/16.
//
#include"math.h"
#ifndef JUNG_PLAYERSCRIPT_H
#define JUNG_PLAYERSCRIPT_H
#include"Script.h"
#include"iostream"
using namespace glm;
using namespace std;

class PlayerScript:public Script {

public:

int x=70;
    void Update(){
      if(IsKeyDown(GLFW_KEY_W))
        model->gameManager->camera->ProcessKeyboard(FORWARD, model->gameManager->deltaTime);
        if(IsKeyDown(GLFW_KEY_S))
            model->gameManager->camera->ProcessKeyboard(BACKWARD, model->gameManager->deltaTime);
        if(IsKeyDown(GLFW_KEY_A))
            model->gameManager->camera->ProcessKeyboard(LEFT, model->gameManager->deltaTime);
        if(IsKeyDown(GLFW_KEY_D))
            model->gameManager->camera->ProcessKeyboard(RIGHT,model->gameManager->deltaTime);
      //  model->gameManager->camera->Position=this->model->position+vec3(0.f,5.f,-2.f);
        if(IsKeyDown(GLFW_KEY_T))
        {

         model->gameManager->camera->Position=Lerp(model->gameManager->camera->Position,this->model->position+vec3(0.f,5.f,-5.f),0.01);
        }
        model->gameManager->camera->ViewMatrix=glm::lookAt(model->gameManager->camera->Position, model->gameManager->camera->Position + model->gameManager->camera->Front, model->gameManager->camera->Up);
        //model->gameManager->camera->ViewMatrix=glm::lookAt(model->gameManager->camera->Position,model->position ,  model->gameManager->camera->Up);

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
            vec3 movTemp=model->direction*0.1f;
            model->SetPosition(vec3(model->position.x+movTemp.x,model->position.y+movTemp.y,model->position.z+movTemp.z));
        }
        if(IsKeyDown(GLFW_KEY_DOWN))
        {
            vec3 pos=model->position;
            vec3 movTemp=-model->direction*0.1f;
            model->SetPosition(vec3(model->position.x+movTemp.x,model->position.y+movTemp.y,model->position.z+movTemp.z));
        }
        if(IsKeyDown(GLFW_KEY_Q))
        {
           model->Rotate(0,1,0,90*model->gameManager->deltaTime);
         //   model->gameManager->camera->RotateAround(model->position,glm::vec3(0,1.,0),90*model->gameManager->deltaTime);
            //model->gameManager->camera->ViewMatrix=glm::lookAt(model->gameManager->camera->Position,model->direction*-1.0f+glm::vec3(0.,3.f,0.) ,  model->gameManager->camera->Up);
        }
        if(IsKeyDown(GLFW_KEY_E))
        {
            model->Rotate(0,1,0,-90*model->gameManager->deltaTime);
        }
        if(IsKeyDown(GLFW_KEY_U))
        {
            model->Rotate(1,0,0,-90*model->gameManager->deltaTime);
        }
        if(IsKeyDown(GLFW_KEY_I))
        {
            model->Rotate(1,0,0,90*model->gameManager->deltaTime);
        }
        if(IsKeyDown(GLFW_KEY_F))
        {

            model->Scale(vec3(0.9f,0.9f,0.9f));
        }
        if(IsKeyDown(GLFW_KEY_G))
        {
            model->Scale(vec3(1.1f,1.1f,1.1f));
        }
        if(IsKeyDown(GLFW_KEY_M))
        {
            model->MoveTo(glm::vec3(5.f,5.f,5.f),0.05f);
        }
        if(IsKeyDown(GLFW_KEY_N))
        {
            model->SetPosition(glm::vec3(5.f,5.f,5.f));
        }
        if(IsKeyDown(GLFW_KEY_R))
        {
            model->RotateAround(vec3(0.f,0.f,0.f),vec3(0.f,1.f,0.f),1.f);
        }
        model->SetRotation(vec3(0, -model->gameManager->camera->Yaw+90 , 0));
        if(IsKeyDown(GLFW_KEY_X)) {

        }
     //   model->gameManager->camera->ViewMatrix=glm::lookAt(model->position-model->direction*4.5f+vec3(0,5.f,0.f),model->position+model->direction+vec3(0,4.f,0),  model->gameManager->camera->Up);
        if(IsKeyDown(GLFW_KEY_C))
        {
            vec3 camVec = model->gameManager->camera->Front;
            vec3 modelVec=model->direction;
            vec2 camVec1=vec2(camVec.x,camVec.z);
            vec2 modelVec1=vec2(modelVec.x,modelVec.z);
            //model->gameManager->camera->RotateAround(model->position,glm::vec3(0,1.,0),model->gameManager->camera->Yaw*model->gameManager->deltaTime);
            model->gameManager->camera->Position=Lerp(model->gameManager->camera->Position,model->position-model->direction*6.f+vec3(0,5.f,0.f),model->gameManager->deltaTime*3);








        }




    }
    void Start(){

        std::cout<<" hello it's me the script component Start!!!";
    }



};


#endif //JUNG_PLAYERSCRIPT_H
