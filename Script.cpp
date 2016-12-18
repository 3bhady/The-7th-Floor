//
// Created by mohamed on 11/12/16.
//
#pragma once

#include "Script.h"
#include "Model.h"
#include "GameManager.h"


Script::Script() {

}
bool Script::IsKeyDown(int key)
{
    model->gameManager->input->IsKeyDown(key);
}
glm::vec3 Script::Lerp(vec3 start,vec3 end,float  interpolationValue)
{
return Script::model->gameManager->input->Lerp(start,end,interpolationValue);
}
void Script::MousePosition(float &x,float& y)
{
  x=  model->gameManager->input->mouseXPosition;
  y=model->gameManager->input->mouseYposition;
}

 void Script::OnCollision(Collision *collision) {

}
void Script::StoreParameters()
{
    model->lastModalMatrix=model->modalMatrix;
    model->lastPosition=model->position;
    model->lastRotation=model->rotation;
    model->lastDirection=model->direction;
    model->lastRight=model->right;

}

void Script::Translate(glm::vec3 Target, float step) {
    glm::vec3 distanceVec =Target  - model->position;

    float x=distanceVec.x;
    float y=distanceVec.y;
    float z=distanceVec.z;
    float distance = x*x + y*y + z*z;
    distance = sqrt(distance);
    if(distance<=0.1f)
        return;
    distanceVec=glm::normalize(distanceVec);
    model->SetPosition(model->position+distanceVec*step);
}
