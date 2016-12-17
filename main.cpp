



#include <iostream>
#include "GameManager.h"
#include "Camera.h"

#include"PlayerScript.h"
#include "Model2D.h"
#include "SwordScript.h"

#include<vector>
#include <glm/gtc/type_ptr.hpp>
GameManager *GM=new GameManager();
//testing section shaders


//shadersss
int main() {
    GM->Init();

    Script * player=new PlayerScript();
    Script* sword=new SwordScript();
   // Model *ourModel=new Model(FileSystem::getPath("objects/cyborg/test.obj"));
   // GM->AddModel(ourModel);
   GM->Create_Object("nanosuit");








    //Model *ourModel=new Model(FileSystem::getPath("objects/cyborg/cyborg.obj"));
    //GM->AddModel(ourModel);
    //GM->Create_Object("nanosuit");

    GM->Create_Object("cyborg");
    GM->gameModel[1]->Tag="cyborg";
    //GM->gameModel[0]->IsAnimated=true;
    GM->gameModel[0]->FramesNumber=1;
    GM->Create_Object("scene");

    GM->Create_Object("test");
    GM->CreateObject2D("cursor");

// Set the required callback functions

  GM->Start(); //call start in all models script component
    Model2D *model2D = new Model2D(std::__cxx11::string());

    GM->gameModel[1]->Tag="scene";

    GM->Create_Object("Walk");


    GM->Create_Object("cyborg");
    GM->gameModel[5]->Trigger(1);
    GM->gameModel[5]->FramesNumber=1;
    GM->gameModel[5]->AttachScript(sword);
    GM->gameModel[5]->Tag="sword";



//GM->gameModel[5]->SetPosition(vec3(0,0,4.0f));
    GM->gameModel[1]->AttachScript(player);
    GM->gameModel[4]->Tag="Animated";
    GM->gameModel[4]->IsAnimated=true;
    GM->gameModel[2]->Trigger(1);
    GM->gameModel[1]->Trigger(1);
    GM->gameModel[4]->FramesNumber=11;



       GM->gameModel[2]->meshes[8].IsTrigger=false;



  GM->Start(); //call start in all models script component

    // Draw in wireframe
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    while(!glfwWindowShouldClose(GM->GetWindow()))
    {
    GM->UpdateGameParameters();

        GM->Update();
        GM->Check_Collision();

      //  GM->gameModel[4]->IsAnimated=false;
      GM->Draw();



    }
    glfwTerminate();
    return 0;
}
//
