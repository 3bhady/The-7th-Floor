//
// Created by mohamed on 17/12/16.
//

#ifndef JUNG_SWORDSCRIPT_H
#define JUNG_SWORDSCRIPT_H
#include"math.h"

#include"Script.h"
#include"iostream"
#include "Collision.h"
#include "Model.h"
#include "PlayerScript.h"

using namespace std;


class SwordScript:public Script {

    void Start(){
model->Scale(vec3(0.2,0.2,0.2));
        model->SetPosition(vec3(0.,0.,5.0));



    }
    void Update(){



    }
void OnCollision(Collision* collision)
{

//cout<<collision->model->Tag;
<<<<<<< HEAD
   // if(((PlayerScript*)model->parent->script)->shouldAttack){
        //cout<<"   "<<collision->model->Tag<<endl;
       // cout<<model->Tag<<endl;
   // }
=======
    if(((PlayerScript*)model->parent->script)->shouldAttack){

    }
>>>>>>> d8bcd81f851b8111f66ca3871f08c46241240e7b

}



};


#endif //JUNG_SWORDSCRIPT_H
