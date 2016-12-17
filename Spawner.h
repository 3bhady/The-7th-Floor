#pragma once
#include "Script.h"
#include "Model.h"

class Spawner : public Script{
    std::vector<Model*> zombies;
public:
    void Start() override {
        int room =0;
        for (int i = 0; i < 25; i++)
        {
            room = int(i/5);
            zombies.push_back(model->gameManager->Inistatiate("cyborg"));
        zombies[i]->SetPosition(glm::vec3(85.0f-2*i-room*30,0.f,27.0f));
        }

        for (int i = 0; i < 25; i++)
        {
            room = int(i/5);
            zombies.push_back(model->gameManager->Inistatiate("cyborg"));
            zombies[zombies.size()-1]->SetPosition(glm::vec3(85.0f-2*i-room*30,0.f,-27.0f));
        }
      /*  for(int i=0;i<5;i++)
        {zombies.push_back(model->gameManager->Inistatiate("cyborg"));
        zombies[zombies.size()-1]->SetPosition(glm::vec3(91.0f-2*i,0.f,27.0f));}

        for(int i=0;i<5;i++)
        {
            zombies.push_back(model->gameManager->Inistatiate("cyborg"));
        zombies[zombies.size()-1]->SetPosition(glm::vec3(48.0f-2*i,0.f,27.0f));
        }
*/
    }

    void Update() override {

    }

    void OnCollision(Collision *collision) override {

    }
};