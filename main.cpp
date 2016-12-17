#include <iostream>
#include "GameManager.h"
#include "Camera.h"
//#include "filesystem.h"
#include"PlayerScript.h"
#include <irrKlang.h>
#include<vector>
#include <glm/gtc/type_ptr.hpp>



GameManager *GM=new GameManager();

//using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")
int main() {

  //  ISoundEngine* engine = irrklang::createIrrKlangDevice();
   // if (!engine)
   // {
   //     printf("Could not startup engine\n");
   //     return 0; // error starting up the engine
   // }


    GM->Init();


Script * player=new PlayerScript();




    //Model *ourModel=new Model(FileSystem::getPath("objects/cyborg/cyborg.obj"));
    //GM->AddModel(ourModel);
    //GM->Create_Object("nanosuit");
   // GM->Create_Object("cyborg");
   // GM->gameModel[0]->Tag="cyborg";
  //  GM->gameModel[0]->FramesNumber=1;


    GM->Create_Object("scene");
    GM->gameModel[0]->Tag="scene";



    GM->Create_Object("nano");
    GM->gameModel[1]->IsAnimated=true;
    GM->gameModel[1]->FramesNumber=61;




// Set the required callback functions
GM->gameModel[1]->AttachScript(player);
  //  GM->gameModel[0]->Trigger(true);
  //  GM->gameModel[1]->Trigger(true);
//GM->gameModel[2]->Trigger(true);
    //GM->gameModel[0]->SetPosition(glm::vec3(0.f,2.f,0));

  GM->Start(); //call start in all models script component

    // Draw in wireframe
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!glfwWindowShouldClose(GM->GetWindow()))
    {
     GM->UpdateGameParameters();
        GM->Check_Collision();
        GM->Update();
        GM->Draw();
    }

    glfwTerminate();
    return 0;
}
