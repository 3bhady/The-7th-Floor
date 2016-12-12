#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include "Mesh.h"

class Collider {
private:
    float x1,y1,z1, //max
            x2,y2,z2; //min
    std::vector<glm::vec3> vertices;
    Mesh* mesh;
public:
    void SetValues(float _x1,float _y1,float _z1, float _x2,float _y2,float _z2 );
    Collider(Mesh * parent);
};
