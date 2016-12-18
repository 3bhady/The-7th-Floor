



#include <iostream>
#include "GameManager.h"
#include "Camera.h"

#include"PlayerScript.h"

//#include <irrKlang.h>

#include "Model2D.h"
#include "Spawner.h"
#include "SwordScript.h"
#include "ZombieBrain.h"


#include<vector>
#include <glm/gtc/type_ptr.hpp>
GameManager *GM=new GameManager();
//testing section shaders


//using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")


//shadersss

int main() {
    GM->Init();
    //GM->CreateObject2D("cursor");
    Script * player=new PlayerScript();

    //Script* sword=new SwordScript();

    //GM->Create_Object("cyborg");
    GM->Create_Object("scene");
    GM->gameModel[0]->Trigger(1);
    GM->gameModel[0]->meshes[8].IsTrigger=false;
    GM->gameModel[0]->Tag="scene";
   // GM->gameModel[0]->AttachScript(new Spawner());
    //GM->Create_Object("cyborg");
    //GM->gameModel[0]->Tag="x";
    //GM->gameModel[2]->Tag="sword";
    //Model2D *model2D = new Model2D(std::__cxx11::string());
//GM->gameModel[2]->SetPosition(vec3(0,0,3.));


    GM->Create_Object("test");
    GM->gameModel[1]->Animate(1);
    GM->gameModel[1]->IsAnimated=1;
    GM->gameModel[1]->FramesNumber=61;
    GM->gameModel[1]->Trigger(1);
    GM->gameModel[1]->AttachScript(player);
    GM->gameModel[1]->Tag="player";

GM->Create_Object("cyborg");
    GM->gameModel[2]->Tag="sword";

 //GM->gameModel[2]->AttachScript(sword);
   //GM->gameModel[2]->Trigger(1);
  //GM->gameModel[0]->Trigger(1);
  //GM->gameModel[1]->Trigger(1);

GM->Create_Object("zombie");
    GM->gameModel[3]->Animate(1);
    GM->gameModel[3]->IsAnimated=1;
    GM->gameModel[3]->FramesNumber=61;
    GM->gameModel[3]->Trigger(1);
    GM->gameModel[3]->Tag="zombie";
    GM->gameModel[3]->SetPosition(glm::vec3(70.f,0.0f,10.f));
    GM->gameModel[3]->AttachScript(new ZombieBrain());










    //GM->gameModel[1]->Tag="scene";





    // GM->gameModel[0]->AttachScript(spawner);







//GM->gameModel[5]->SetPosition(vec3(0,0,4.0f));





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
