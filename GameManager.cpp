//
// Created by mohamed on 22/11/16.
//

#include "GameManager.h"
//#include "Object.h"

//class Object;//will be needed

void Game_Manager::Init() {
//todo:implement loading of the scene objects
    //load tag , position and orientation

    GLuint screenWidth = 800, screenHeight = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(screenWidth, screenHeight, "7th-Floor", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);



    // Options
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    shader=new Shader("shader.vs", "shader.frag");

}

void Game_Manager::Start() {
    LoadScene();
    //todo:use LoadScene to create the objects of the scene
    //Create_Object()




    //todo:bind the program and do the necessary checks to opengl
}

//not sure if tag is string or not

void Game_Manager::Create_Object(std::string tag) {
//todo:create an object using tag and add it to the list of objects
//if(tag=="NanoSuit")
   // this->Hierarchy.push_back(new Model());

}

void Game_Manager::Update() {
//todo:loop on the object list and call update function in every object
}

void Game_Manager::Check_Collision() {
//todo:check for collisions in all the objects
}

void Game_Manager::LoadScene() {
//todo:implement loading scene objects data from file
}

void Game_Manager::Destroy_Object() {
//todo:implement how the object is removed from the list
}
void Game_Manager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* Game_Manager::GetWindow(){
    return window;
}