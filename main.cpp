#include <iostream>
#include "GameManager.h"
#include "Camera.h"
#include "filesystem.h"
#include"PlayerScript.h"
#include <glm/gtc/type_ptr.hpp>
bool keys[1024];
Camera *camera= new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
GLuint screenWidth = 800, screenHeight = 600;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool c=false;
GLfloat xoffset = 0;
GLfloat yoffset =0;
void Do_Movement();

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
GameManager *GM=new GameManager();


int main() {

//GM.camera->Init(glm::vec3(0.0f, 0.0f, 3.0f));
  //  GM->camera=camera;
    GM->Init();

    GM->shader->Use();



   // GM->input->gameManager=GM;

Script * player=new PlayerScript();

    // <-- Don't forget this one!
   // Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    Model ourModel(FileSystem::getPath("objects/nanosuit/nanosuit.obj"));
    Model ourModel2(FileSystem::getPath("objects/nanosuit/nanosuit.obj"));
// Set the required callback functions
ourModel.AttachScript(player);
    ourModel.script->Start();

    // Draw in wireframe
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
GLFWwindow* window = GM->GetWindow();

  // glfwSetKeyCallback(window, key_callback);
  // glfwSetCursorPosCallback(window, mouse_callback);
   //glfwSetScrollCallback(window, scroll_callback);

    while(!glfwWindowShouldClose(window))
    {

        // Set frame time
    // GM.UpdateDeltaTime();
        // Check and call events
      //  GM->UpdatePollEvents();
        Do_Movement();
        //GM.Do_Movement();
        // Clear the colorbuffer

        // Transformation matrices
     //  GM->camera->ProjectionMatrix = glm::perspective(GM->camera->Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

     GM->UpdateGameParameters();
    //  GM.camera->ViewMatrix=GM.camera->GetViewMatrix()*glm::translate(glm::mat4(),glm::vec3(0.4,0.4,0.4));
     // glUniformMatrix4fv(glGetUniformLocation(GM.shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr( GM.camera->ProjectionMatrix));
       // glUniformMatrix4fv(glGetUniformLocation(GM.shader->Program, "view"), 1, GL_FALSE, glm::value_ptr( GM.camera->ViewMatrix));

        // Draw the loaded model
        glm::mat4 model;
       // model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// It's a bit too big for our scene, so scale it down
 ourModel.modalMatrix=model;
        //glUniformMatrix4fv(glGetUniformLocation(GM->shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glClearColor(0.5f, 0.05f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       // model = glm::translate(model, glm::vec3(1.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene

        glm::mat4 model2 ;
     // Translate it down a bit so it's at the center of the scene
        model2 = glm::scale(model2, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
        model2 = glm::translate(model, glm::vec3(5.f, -1.75f, 0.0f));
        ourModel2.modalMatrix=model2;
        ourModel.Draw(GM->shader);
        ourModel2.Draw(GM->shader);

        // Swap the buffers
        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;
}
void Do_Movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W]){c=true;
        GM->camera->ProcessKeyboard(FORWARD, GM->deltaTime);}
    else c=false;
    if(keys[GLFW_KEY_S])
        GM->camera->ProcessKeyboard(BACKWARD, GM->deltaTime);
    if(keys[GLFW_KEY_A])
        GM->camera->ProcessKeyboard(LEFT, GM->deltaTime);
    if(keys[GLFW_KEY_D])
        GM->camera->ProcessKeyboard(RIGHT, GM->deltaTime);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

     xoffset = xpos - lastX;
     yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;
    GM->camera->ProcessMouseMovement(xoffset, yoffset);


}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}