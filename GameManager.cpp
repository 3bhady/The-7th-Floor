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
    shader2D=new Shader("shader2D.vs","shader2D.frag");

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

        gameModel[i]->script->Update();
        gameModel[i]->RePosition();
    }
    camera->ProjectionMatrix = glm::perspective(camera->Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 200.0f);

//custom view matrix
    camera->ViewMatrix= camera->GetViewMatrix(1);
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(camera->ProjectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(camera->ViewMatrix));
}

void GameManager::Draw() {
    glm::vec3 lightPos=gameModel[1]->position;
    lightPos+=glm::vec3(0,15,0);
//order is very important , playing with it will be catastrophic !
    glClearColor(0.5f, 0.05f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->Use();
   glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(camera->ProjectionMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(camera->ViewMatrix));
    glUniform3fv(glGetUniformLocation(shader->Program, "lightPos"), 1, &(lightPos[0]));
   for(int i=0; i<gameModel.size(); i++)
    {
        gameModel[i]->Draw(shader);
    }
    //now 2d objects
    shader2D->Use();
    for(int i=0; i<gameModel2D.size(); i++)
    {
        gameModel2D[i]->Draw(shader2D);
    }

    glfwSwapBuffers(window);
}
void GameManager::AddModel(Model*& m )
{
gameModel.push_back(m);
    m->gameManager=this;

}
void GameManager::AddModel2D(Model2D*& m)
{
    gameModel2D.push_back(m);
}

//not sure if tag is string or not

void GameManager::Create_Object(std::string tag) {
//todo:create an object using tag and add it to the list of objects
//if(tag=="NanoSuit")
   // this->Hierarchy.push_back(new Model());
for(int i=0; i<gameModel.size(); i++)
{
    if(gameModel[i]->Tag==tag){
   Model* m= new Model();
        m->textures_loaded=gameModel[i]->textures_loaded;
        m->Tag=tag;
       // model->FramesNumber=gameModel[i]->FramesNumber;
        for(int j=0; j<gameModel[i]->meshes.size(); j++)
            m->meshes.push_back(gameModel[i]->meshes[j].CreateMeshInstanse(m));


       AddModel(m);

    return;
    }
}
    if(tag=="cyborg")
    gameModel.push_back( new Model(FileSystem::getPath("objects/cyborg/cyborg.obj"),"cyborg") );
    if(tag=="nanosuit")
        gameModel.push_back(new Model(FileSystem::getPath("objects/nanosuit/nanosuit.obj"),"nanosuit") );
    if(tag=="scene")
        gameModel.push_back(new Model(FileSystem::getPath("objects/7th/X.obj"),"scene"));

    if(tag=="Walk")
        gameModel.push_back(new Model(FileSystem::getPath("objects/Animation/Walk.obj"),"Walk"));

    if(tag=="swordfront")
        gameModel.push_back(new Model(FileSystem::getPath("objects/swordfront/swordfront.obj"),"swordfront"));

    if(tag=="zombie")
    {gameModel.push_back(new Model(FileSystem::getPath("objects/zombie/untitled.obj"),"zombie"));
    gameModel[gameModel.size()-1]->Animate(1);
        gameModel[gameModel.size()-1]->FramesNumber=61;
    }

if(tag=="test")
{gameModel.push_back(new Model(FileSystem::getPath("objects/TEST/TEST.obj"),"test"));
    gameModel[gameModel.size()-1]->Animate(1);
    gameModel[gameModel.size()-1]->FramesNumber=61;
}

gameModel[gameModel.size()-1]->gameManager=this;

}
void GameManager::CreateObject2D(std::string tag)
{
    gameModel2D.push_back(new Model2D(tag));
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

Model *GameManager::Inistatiate(string tag) {
   Create_Object( tag);
    return gameModel[gameModel.size()-1];
}

Model *GameManager::GetModelByTag(string tag) {
    for(int i=0; i<gameModel.size(); i++)
    {
        if(gameModel[i]->Tag==tag)return  gameModel[i];
    }
    return nullptr;
}
