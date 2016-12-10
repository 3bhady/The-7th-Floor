#include <iostream>
#include "GameManager.h"
#include "Camera.h"
#include "filesystem.h"
#include <glm/gtc/type_ptr.hpp>
bool keys[1024];
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
GLuint screenWidth = 800, screenHeight = 600;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
void Do_Movement();

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {


    Game_Manager GM;
    GM.Init();
   // Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Model ourModel(FileSystem::getPath("objects/nanosuit/nanosuit.obj"));
// Set the required callback functions

    // Draw in wireframe
  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
GLFWwindow* window = GM.GetWindow();

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

glm::mat4 first = camera.GetViewMatrix();
    glm::mat4 second = first;
//ourModel.Scale(0.2f,0.2f,0.2f);
    // Game loop
    //ourModel.Scale(0.2f,0.2f,0.2f);
    //ourModel.SetPosition(glm::vec3(0.0f, -1.75f, 0.0f));
    while(!glfwWindowShouldClose(window))
    {

        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.05f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GM.shader->Use();   // <-- Don't forget this one!
        // Transformation matrices
        glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);

       // glm::mat4 view = ca.mera.GetViewMatrix();
     /*   second = camera.GetViewMatrix();
        if(first!=second)
        {
            std:: cout<<"changed"<<std::endl;
            second = first;
        }*/
        glm::mat4 view = camera.GetViewMatrix()*glm::translate(glm::mat4(),glm::vec3(0.4,0.4,0.4));
        glUniformMatrix4fv(glGetUniformLocation(GM.shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(GM.shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down

        glUniformMatrix4fv(glGetUniformLocation(GM.shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(ourModel.modalMatrix));
        ourModel.Draw(GM.shader);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
void Do_Movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
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

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}