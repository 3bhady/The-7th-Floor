//
// Created by mohamed on 11/12/16.

#include"GameManager.h"
#include "Input.h"

 GameManager* Input::gameManager= new GameManager();
bool Input::keys[]={0};
GLfloat Input:: mouseXPosition=0;
GLfloat Input::mouseYposition=0;
bool Input::firstMouse=true;
double  Input::lastX=0;
double Input::lastY=0;
GLfloat  Input:: xOffset=0;
GLfloat Input:: yOffset=0;
Input::Input(GameManager* gmf){
 this->gameManager=gmf;
}

   void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
 if(firstMouse)
 {
  lastX = xpos;
  lastY = ypos;
  firstMouse = false;
 }

 xOffset = xpos - lastX;
 yOffset = lastY - ypos;
 lastX = xpos;
 lastY = ypos;

 gameManager->camera->ProcessMouseMovement(xOffset,yOffset);
//std::cout<<"offset " <<xOffset<<std::endl;

}
 void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  gameManager->camera->ProcessMouseScroll(yoffset);
}
