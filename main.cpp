



#include <iostream>
#include "GameManager.h"


#include "Camera.h"

#include"PlayerScript.h"

//#include <irrKlang.h>

#include "Model2D.h"

#include "Spawner.h"
#include "SwordScript.h"
#include "ZombieBrain.h"

#include "SwordScript.h"
#include"GL/glut.h"
#include"GL/freeglut.h"


#include<GL/freeglut.h>
#include<vector>
#include <glm/gtc/type_ptr.hpp>
GameManager *GM=new GameManager();
//testing section shaders

#include<irrKlang.h>
//using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")


//shadersss

int main() {

    GM->Init();
    //GM->CreateObject2D("cursor");
    Script * player=new PlayerScript();


    Script* sword=new SwordScript();

    GM->Create_Object("cyborg");
    GM->Create_Object("scene");
    //GM->gameModel[1]->AttachScript(new Spawner());
    GM->Create_Object("cyborg");
    GM->CreateObject2D("healthBar");
    GM->CreateObject2D("healthBarBackGround");
    GM->gameModel2D[1]->rgb=glm::vec3(1.,0.1,0.1);
    GM->gameModel[0]->Tag="player";
    GM->gameModel[2]->Tag="sword";

   /* GM->Create_Object("zombie");
    GM->gameModel[3]->Trigger(1);
    GM->gameModel[3]->IsAnimated=true;
    GM->gameModel[3]->FramesNumber=61;
    GM->gameModel[3]->SetPosition(vec3(70.0f,0.0,3.0));
    GM->gameModel[3]->AttachScript(new ZombieBrain());
    GM->gameModel[3]->Tag="zombie";

    GM->Create_Object("zombie");
    GM->gameModel[4]->Trigger(1);
    GM->gameModel[4]->IsAnimated=true;
    GM->gameModel[4]->FramesNumber=61;
    GM->gameModel[4]->SetPosition(vec3(50.0f,0.0,3.0));
    GM->gameModel[4]->AttachScript(new ZombieBrain());
    GM->gameModel[4]->Tag="zombie";*/
  //  GM->gameModel[3]->AttachScript(new ZombieBrain());
    // Model2D *model2D = new Model2D(std::__cxx11::string());
GM->gameModel[2]->SetPosition(vec3(0,0,3.));

    GM->gameModel[0]->AttachScript(player);
    GM->gameModel[0]->Tag="player";

 GM->gameModel[2]->AttachScript(sword);
   GM->gameModel[2]->Trigger(1);
  GM->gameModel[0]->Trigger(1);
  GM->gameModel[1]->Trigger(1);
    GM->gameModel[2]->Trigger(1);



    GM->gameModel[0]->FramesNumber=61;
    GM->gameModel[0]->SpritesNumber=16;
    GM->gameModel[0]->IsAnimated=true;





    GM->gameModel[1]->meshes[8].IsTrigger=false;
    GM->gameModel[1]->meshes[31].IsTrigger=false;
    GM->gameModel[1]->meshes[55].IsTrigger=false;

    GM->gameModel[1]->Tag="scene";









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
