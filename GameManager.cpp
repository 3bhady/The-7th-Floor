//
// Created by mohamed on 22/11/16.
//

#include "GameManager.h"

//#include "Object.h"

//class Object;//will be needed
GameManager::GameManager(){
    //definition of input

}
void GameManager::Init() {
//todo:implement loading of the scene objects
    //load tag , position and orientation
    input=new Input(this);
    camera=new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(screenWidth, screenHeight, "7th-Floor", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window,input->key_callback);//setting keyboard call back
    glfwSetCursorPosCallback(window, input->mouse_callback);//setting mouse movement call back
    glfwSetScrollCallback(window, input->scroll_callback);//setting scrolling callback



   // glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);


    // Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
//updating delta time
void GameManager::UpdateDeltaTime() {


    GLfloat currentFrame = glfwGetTime();
    this->deltaTime = currentFrame - lastFrame;
    this->lastFrame = currentFrame;

}
void GameManager::UpdatePollEvents(){

    glfwPollEvents();
}
void GameManager::UpdateGameParameters(){
    UpdatePollEvents();
    UpdateDeltaTime();
   // camera->ProcessMouseMovement(input->xOffset,input->yOffset); //Update Camera will be removed to any of scripts soon :)
    camera->ProjectionMatrix = glm::perspective(camera->Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);


    camera->ViewMatrix= camera->GetViewMatrix()*glm::translate(glm::mat4(),glm::vec3(0.4,0.4,0.4));
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(camera->ProjectionMatrix));
   glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(camera->ViewMatrix));


}

void GameManager::Start() {
    LoadScene();
    //todo:use LoadScene to create the objects of the scene
    //Create_Object()




    //todo:bind the program and do the necessary checks to opengl
}

//not sure if tag is string or not

void GameManager::Create_Object(std::string tag) {
//todo:create an object using tag and add it to the list of objects
//if(tag=="NanoSuit")
   // this->Hierarchy.push_back(new Model());

}

void GameManager::Update() {
//todo:loop on the object list and call update function in every object
}

void GameManager::Check_Collision() {
//todo:check for collisions in all the objects
}

void GameManager::LoadScene() {
//todo:implement loading scene objects data from file
}

void GameManager::Destroy_Object() {
//todo:implement how the object is removed from the list
}


GLFWwindow* GameManager::GetWindow(){
    return window;
}