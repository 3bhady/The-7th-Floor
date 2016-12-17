//
// Created by mohamed on 22/11/16.
//

#include "GameManager.h"
#include "Collision.h"
#include "filesystem.h"

//#include "Object.h"

//class Object;//will be needed
GameManager::GameManager(){
    //definition of input

}
void GameManager::Init( GLuint screenWidth , GLuint screenHeight,std::string windowName) {
//todo:implement loading of the scene objects
    //load tag , position and orientation
    input=new Input(this);
    camera=new Camera(glm::vec3(0.0f, 0.0f, 0.0f));
    this->screenHeight=screenHeight;
    this->screenWidth=screenWidth;
   this->windowName=windowName;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), nullptr, nullptr); // Windowed
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


    shader->Use();//use this shader that we initialized now  ( written by ali : 21  in math ) :) :) :)

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



}

void GameManager::Start() {
    for(int i=0; i<gameModel.size(); i++)
    {
        gameModel[i]->script->Start();
    }
}

void GameManager::Update() {
    for(int i=0; i<gameModel.size(); i++)
    {
        gameModel[i]->RePosition();
        gameModel[i]->script->Update();
    }
    camera->ProjectionMatrix = glm::perspective(camera->Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 200.0f);

//custom view matrix
    camera->ViewMatrix= camera->GetViewMatrix(1);
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(camera->ProjectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(camera->ViewMatrix));
}

void GameManager::Draw() {

//order is very important , playing with it will be catastrophic !
    glClearColor(0.5f, 0.05f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i=0; i<gameModel.size(); i++)
    {
        gameModel[i]->Draw(shader);
    }
    glfwSwapBuffers(window);
}
void GameManager::AddModel(Model*& m )
{
gameModel.push_back(m);
    m->gameManager=this;

}

//not sure if tag is string or not

void GameManager::Create_Object(std::string tag) {
//todo:create an object using tag and add it to the list of objects
//if(tag=="NanoSuit")
   // this->Hierarchy.push_back(new Model());

    if(tag=="cyborg")
    gameModel.push_back( new Model(FileSystem::getPath("objects/cyborg/cyborg.obj")) );
    if(tag=="nanosuit")
        gameModel.push_back(new Model(FileSystem::getPath("objects/nanosuit/nanosuit.obj")) );
    if(tag=="scene")
        gameModel.push_back(new Model(FileSystem::getPath("objects/7th/X.obj")));
    if(tag=="A")
        gameModel.push_back(new Model(FileSystem::getPath("objects/Animation/Walk.obj")));
    if(tag=="nano")
        gameModel.push_back(new Model(FileSystem::getPath("objects/zombie/untitled.obj")) );
gameModel[gameModel.size()-1]->gameManager=this;

}



void GameManager::Check_Collision() {
//todo:check for collisions in all the objects
    for(int i=0;i<gameModel.size();i++)
    {
        for(int j=i+1;j<gameModel.size();j++)
        {
            //vector indicating collisions
           std::vector<pair<Mesh*,Mesh*> >* CollVec= gameModel[i]->IsCollide(gameModel[j]);
            if(CollVec->size()!=0)
            {
                for(int k=0;k<CollVec->size();k++)
                {
                    Collision * collision = new Collision((*CollVec)[k].first,(*CollVec)[k].second);
                gameModel[i]->OnCollision(collision);
                collision = new Collision((*CollVec)[k].second,(*CollVec)[k].first);
                gameModel[j]->OnCollision(collision);

                }
            }

        }
    }
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