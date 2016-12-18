#pragma once
#include "Script.h"
#include "Model.h"
#include "ZombieBrain.h"
class Spawner : public Script{
    std::vector<Model*> zombies;
public:
    void Start() override {
        GameManager* GM= model->gameManager;
        int room =0;
        for (int i = 0; i < 10; i++)
        {
            room = int(i/5);
            GM->Create_Object("zombie");
            zombies.push_back(GM->gameModel[GM->gameModel.size()-1]);//Inistatiate("zombie"));
            zombies[zombies.size()-1]->SetPosition(glm::vec3(85.0f-5*i-room*40,0.f,27));//27.0f));
            zombies[zombies.size()-1]->IsAnimated=true;
            zombies[zombies.size()-1]->FramesNumber=61;
            zombies[zombies.size()-1]->Trigger(1);
            zombies[zombies.size()-1]->AttachScript(new ZombieBrain());
            zombies[zombies.size()-1]->Scale(glm::vec3(2.5,2.5,2.5));
        }




     /*   for (int i = 0; i < 25; i++)
        {
            room = int(i/5);
            GM->Create_Object("zombie");
            zombies.push_back(GM->gameModel[GM->gameModel.size()-1]);
            zombies[zombies.size()-1]->SetPosition(glm::vec3(85.0f-2*i-room*30,0.f,-27.0f));
            zombies[zombies.size()-1]->AttachScript(new ZombieBrain());
            zombies[zombies.size()-1]->Trigger(1);
        }*/
      /*  for(int i=0;i<5;i++)
        {zombies.push_back(model->gameManager->Inistatiate("cyborg"));
        zombies[zombies.size()-1]->SetPosition(glm::vec3(91.0f-2*i,0.f,27.0f));}

        for(int i=0;i<5;i++)
        {
            zombies.push_back(model->gameManager->Inistatiate("cyborg"));
        zombies[zombies.size()-1]->SetPosition(glm::vec3(48.0f-2*i,0.f,27.0f));
        }
*/
        GM= nullptr;
    }

    void Update() override {

    }

    void OnCollision(Collision *collision) override {

    }
};