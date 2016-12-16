//
// Created by mohamed on 11/12/16.
//

#ifndef JUNG_SCRIPT_H
#define JUNG_SCRIPT_H

#include <glm/vec3.hpp>
#include"iostream"

class Model;
class Script {
public:
    Model* model;

Script();
virtual void Start() {
//std::cout<<"this is the script base class Start";
}
 virtual    void Update(){
//     std::cout<<"this is the script base class Update";
    }
bool IsKeyDown(int key);
    glm::vec3 Lerp(glm::vec3 start,glm::vec3 end,float  interpolationValue);

};


#endif //JUNG_SCRIPT_H
