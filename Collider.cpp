#include "Collider.h"

Collider::Collider(Mesh * parent) {
mesh = parent;
    vertices.push_back(glm::vec3(0,0,0));
    vertices.push_back(glm::vec3(0,0,0));
}

void Collider::SetValues(float _x1,float _y1,float _z1, float _x2,float _y2,float _z2  )
{
    x1=_x1;
    x2=_x2;
    y1=_y1;
    y2=_y2;
    z1=_z1;
    z2=_z2;

    vertices[0].x=x1;
    vertices[0].x=y1;
    vertices[0].x=z1;

    vertices[1].x=x2;
    vertices[1].x=y2;
    vertices[1].x=z2;
}
