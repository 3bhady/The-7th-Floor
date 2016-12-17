//
// Created by mohamed on 12/12/16.
//
#include"math.h"
#ifndef JUNG_PLAYERSCRIPT_H
#define JUNG_PLAYERSCRIPT_H
#include"Script.h"
#include"iostream"
#include "Collision.h"

using namespace glm;
using namespace std;

class PlayerScript:public Script {

public:
    glm::vec3 lastPosition;
string lastColliderTag=" x";
float x,y;
    int i=0;
    bool bol=true,colliding=false;
    void Update() {

      StoreParameters();
        MousePosition(x, y);

        if (IsKeyDown(GLFW_KEY_O)) {
            this->model->IsAnimated = false;
        }
        if (IsKeyDown(GLFW_KEY_P)) {
            this->model->IsAnimated = true;
        }

        if (IsKeyDown(GLFW_KEY_I)) {
            bol = false;
            Model *temp = model->gameManager->Inistatiate("Walk");
            temp->SetPosition(model->position + model->direction * 2.0f);
            temp->IsAnimated = true;

        }

        if (IsKeyDown(GLFW_KEY_W)) {
            model->gameManager->camera->ProcessKeyboard(FORWARD, model->gameManager->deltaTime);
        }

        if (IsKeyDown(GLFW_KEY_S))
            model->gameManager->camera->ProcessKeyboard(BACKWARD, model->gameManager->deltaTime);
        if (IsKeyDown(GLFW_KEY_A))
            model->gameManager->camera->ProcessKeyboard(LEFT, model->gameManager->deltaTime);
        if (IsKeyDown(GLFW_KEY_D))
            model->gameManager->camera->ProcessKeyboard(RIGHT, model->gameManager->deltaTime);
        //  model->gameManager->camera->Position=this->model->position+vec3(0.f,5.f,-2.f);
        if (IsKeyDown(GLFW_KEY_T)) {

            model->gameManager->camera->Position = Lerp(model->gameManager->camera->Position,
                                                        this->model->position + vec3(0.f, 5.f, -5.f), 0.01);
        }
        model->gameManager->camera->ViewMatrix = glm::lookAt(model->gameManager->camera->Position,
                                                             model->gameManager->camera->Position +
                                                             model->gameManager->camera->Front,
                                                             model->gameManager->camera->Up);
        //model->gameManager->camera->ViewMatrix=glm::lookAt(model->gameManager->camera->Position,model->position ,  model->gameManager->camera->Up);


        if (IsKeyDown(GLFW_KEY_RIGHT)) {
            vec3 pos = model->position;
            vec3 movTemp = model->right * 0.1f;
            model->SetPosition(
                    vec3(model->position.x + movTemp.x, model->position.y + movTemp.y, model->position.z + movTemp.z));
        }
        if (IsKeyDown(GLFW_KEY_LEFT)) {
            vec3 pos = model->position;
            vec3 movTemp = -model->right * 0.1f;
            model->SetPosition(
                    vec3(model->position.x + movTemp.x, model->position.y + movTemp.y, model->position.z + movTemp.z));
        }
        if (IsKeyDown(GLFW_KEY_UP)) {
            vec3 pos = model->position;
            vec3 movTemp = model->direction * 0.1f;

            model->SetPosition(
                    vec3(model->position.x + movTemp.x, model->position.y + movTemp.y, model->position.z + movTemp.z));
            cout<<endl<<"  position "<<" x - y - z  "<<model->position.x<<" "<<model->position.y<<" "<<model->position.z<<endl;
        }
        if (IsKeyDown(GLFW_KEY_DOWN)) {
            vec3 pos = model->position;
            vec3 movTemp = -model->direction * 0.1f;

            model->SetPosition(
                    vec3(model->position.x + movTemp.x, model->position.y + movTemp.y, model->position.z + movTemp.z));
        }

        if(IsKeyDown(GLFW_KEY_J))
        {


            model->SetPosition(vec3(model->position.x,model->position.y+0.09f,model->position.z));
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
            model->gameManager->camera->Position=Lerp(model->gameManager->camera->Position,model->position-model->direction*5.f+vec3(0,5.f,0.f),model->gameManager->deltaTime*3);

        }





    }
  void  OnCollision(Collision* collision )
  {
  //    cout<<endl<<" current position "<<" x - y - z  "<<model->position.x<<" "<<model->position.y<<" "<<model->position.z<<endl;
//     cout<<" old  position "<<" x - y - z  "<<model->lastPosition.x<<" "<<model->lastPosition.y<<" "<<model->lastPosition.z<<endl;
model->modalMatrix=model->lastModalMatrix;
      model->position=model->lastPosition;
      model->rotation=model->lastRotation;
      model->direction=model->lastDirection;
      model->right=model->lastRight;

  }
    void Start(){
model->SetPosition(glm::vec3(0.,0.,0.f));
        std::cout<<" hello it's me the script component Start!!!";
     // model->SetPosition(vec3(0,0,13.36));
    }
void StoreParameters()
{
model->lastModalMatrix=model->modalMatrix;
    model->lastPosition=model->position;
    model->lastRotation=model->rotation;
    model->lastDirection=model->direction;
    model->lastRight=model->right;

}


};


#endif //JUNG_PLAYERSCRIPT_H
