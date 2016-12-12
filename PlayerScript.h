//
// Created by mohamed on 12/12/16.
//

#ifndef JUNG_PLAYERSCRIPT_H
#define JUNG_PLAYERSCRIPT_H
#include"Script.h"
#include"iostream"
class PlayerScript:public Script {

public:


    void Update(){


        std::cout<<" hello it's me the script component Update!!!";
    }
    void Start(){

        std::cout<<" hello it's me the script component Start!!!";
    }



};


#endif //JUNG_PLAYERSCRIPT_H
