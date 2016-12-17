



#include <iostream>
#include "GameManager.h"
#include "Camera.h"

#include"PlayerScript.h"

#include <irrKlang.h>

#include "Model2D.h"

#include<vector>
#include <glm/gtc/type_ptr.hpp>
GameManager *GM=new GameManager();
//testing section shaders


//using namespace irrklang;
//#pragma comment(lib, "irrKlang.lib")


//shadersss

int main() {
    GM->Init();

    Script * player=new PlayerScript();

  // GM->Create_Object("nanosuit");

    GM->Create_Object("scene");

    //GM->Create_Object("test");
    GM->CreateObject2D("cursor");

    Model2D *model2D = new Model2D(std::__cxx11::string());

    GM->gameModel[0]->Tag="scene";

    GM->Create_Object("cyborg");
    GM->gameModel[1]->AttachScript(player);
    GM->gameModel[1]->Tag="Animated";
    //GM->gameModel[1]->IsAnimated=true;
    //GM->gameModel[1]->FramesNumber=2;

    GM->gameModel[0]->Trigger(1);
    GM->gameModel[1]->Trigger(1);




       GM->gameModel[0]->meshes[8].IsTrigger=false;



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
