



#include <iostream>
#include "GameManager.h"
#include "Camera.h"

#include"PlayerScript.h"

//#include <irrKlang.h>

#include "Model2D.h"
#include "SwordScript.h"

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

    Script* sword=new SwordScript();

    GM->Create_Object("cyborg");
    GM->Create_Object("scene");
    GM->Create_Object("cyborg");
    GM->gameModel[0]->Tag="x";
    GM->gameModel[2]->Tag="sword";
    Model2D *model2D = new Model2D(std::__cxx11::string());
GM->gameModel[2]->SetPosition(vec3(0,0,3.));

    GM->gameModel[0]->AttachScript(player);

 GM->gameModel[2]->AttachScript(sword);
   GM->gameModel[2]->Trigger(1);
  GM->gameModel[0]->Trigger(1);
  GM->gameModel[1]->Trigger(1);








    GM->gameModel[1]->meshes[8].IsTrigger=false;



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
