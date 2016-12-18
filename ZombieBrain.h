#pragma once

#include "Script.h"
#include "Model.h"
#include "Collision.h"

class ZombieBrain : public Script{
public:
    Model * player;
    glm::vec3 lastpos;
    int a,b,c;
    void Start() override {
        lastpos=model->position;

        int  a =random()%100;
        a = random()%2?-1*a:a;

        int b =random()%100;
        b= random()%2?-1*b:b;
        int c =random()%100;
        c=random()%2?-1*c:c;



int size =model->gameManager->gameModel.size();
        GameManager* GM=model->gameManager;

        for(int i=0;i<size;i++)
        {
            if(GM->gameModel[i]->Tag=="player")
            {
                player=GM->gameModel[i];
            break;
            }
        }

    }

    void Update() override {
        StoreParameters();

        glm::vec3 distanceVec =player->position  - model->position;

        float x=distanceVec.x;
        float y=distanceVec.y;
        float z=distanceVec.z;
        float distance = x*x + y*y + z*z;
        distance = sqrt(distance);
        //  std::cout<<distance<<endl;

if(distance <2)
{
    return;
}

        if(distance<=3) //if the distance is small move towards the player
        {
            //cout<<"moving towards char"<<endl;
           // model->MoveTo(player->position,0.01f);
           Translate(player->position,0.1f);
            if(lastpos==model->position) { //if movement in the last frame hasen't been successful move to a random position
                 a = random() % 100;
                a = random() % 2 ? -a : a;
                 b = random() % 100;
                b = random() % 2 ? -b : b;
                 c = random() % 100;
                c = random() % 2 ? -c : c;
               // model->SetPosition(Lerp(model->position, glm::vec3(a, 0, c), 0.0008f));
                Translate(glm::vec3(a, 0, c), 0.1f);
            }
            else
            {
                lastpos = model->position;
            }
        }
        else
        {
            if(lastpos==model->position) //if movement in the last frame hasen't been successful move to a random position
            {   a =random()%100;
            a = random()%2?-1*a:a;

             b =random()%100;
            b= random()%2?-1*b:b;
             c =random()%100;
            c=random()%2?-1*c:c;}
            else
            {lastpos = model->position;}

            //if the movement in the last frame has been successful continue moving to the direction
           // model->SetPosition(Lerp(model->position,glm::vec3(a,0,c),0.0008f));
            Translate(glm::vec3(a, 0, c), 0.1f);
        }

    }

    void OnCollision(Collision *collision) override {
      //  std::cout<<collision->model->Tag<<std::endl;
        model->modalMatrix=model->lastModalMatrix;
        model->position=model->lastPosition;
        model->rotation=model->lastRotation;
        model->direction=model->lastDirection;
        model->right=model->lastRight;
    }
~ZombieBrain(){
    player= nullptr;
    model=nullptr;
}
};