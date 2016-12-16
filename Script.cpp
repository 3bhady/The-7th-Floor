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
return model->gameManager->input->Lerp(start,end,interpolationValue);
}
