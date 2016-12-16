//
// Created by mohamed on 11/12/16.
//

#ifndef JUNG_INPUT_H
#define JUNG_INPUT_H

#include <GLFW/glfw3.h>
#include "GameManager.h"

class GameManager;

class Input {
private://mouse properties


public:
    static GameManager* gameManager;
    static  double lastX;
    static  double lastY;
    static  GLfloat xOffset;
    static  GLfloat yOffset;
    static bool firstMouse;
    GLFWwindow * window;
    static   bool keys[1024];
    static  GLfloat  mouseXPosition;
    static   GLfloat mouseYposition;
    // Is called whenever a key is pressed/released via GLFW
    static   void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if(action == GLFW_PRESS)
        keys[key]=true;
        else if(action == GLFW_RELEASE)
            keys[key]=false;
    }
   static  bool IsKeyDown(int key)
    {
        return keys[key];
    }
     glm::vec3 Lerp(glm::vec3 start,glm::vec3 end,float  interpolationValue){

         bool shouldReturn =true;
         double xDifference=abs((end.x-start.x));
         double yDifference=abs((end.y-start.y));
         double zDifference=abs((end.z-start.z));
         if((xDifference>=0&&xDifference<=0.1)&&(yDifference>=0&&yDifference<=0.19)&&(zDifference>=0&&zDifference<=0.1) ){
             return start;
         }



         glm::vec3 nextPosition= start+interpolationValue*(end-start);

       return nextPosition;
     }



  static   void mouse_callback(GLFWwindow* window, double xpos, double ypos);


   static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


Input(GameManager* gmf);

};


#endif //JUNG_INPUT_H
//
//
// Created by mohamed on 11/12/16.
//



