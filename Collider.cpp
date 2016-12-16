#include "Collider.h"
#include "Model.h"

Collider::Collider(Mesh * parent) {
mesh = parent;
    parent= nullptr;
   // vertices.push_back(glm::vec4(0,0,0,1));
   // vertices.push_back(glm::vec4(0,0,0,1));
}

void Collider::SetValues(float _x1,float _y1,float _z1, float _x2,float _y2,float _z2  )
{

    x1=_x1;
    x2=_x2;
    y1=_y1;
    y2=_y2;
    z1=_z1;
    z2=_z2;

    X1=_x1;
    X2=_x2;
    Y1=_y1;
    Y2=_y2;
    Z1=_z1;
    Z2=_z2;


    vertices.push_back(glm::vec4(x1,y1,z1,1.f));
    vertices.push_back(glm::vec4(x1,y1,z2,1.f));
    vertices.push_back(glm::vec4(x1,y2,z1,1.f));
    vertices.push_back(glm::vec4(x1,y2,z2,1.f));
    vertices.push_back(glm::vec4(x2,y1,z1,1.f));
    vertices.push_back(glm::vec4(x2,y1,z2,1.f));
    vertices.push_back(glm::vec4(x2,y2,z1,1.f));
    vertices.push_back(glm::vec4(x2,y2,z2,1.f));

}

bool Collider::IsCollide(Collider * collider) {
    //this->RePosition();
    //collider->RePosition(); //todo: reposition is being called twice !
    float a1,b1,c1 //max
    ,a2,b2,c2;//min
    a1=collider->x1;
    a2=collider->x2;
    b1=collider->y1;
    b2=collider->y2;
    c1=collider->z1;
    c2=collider->z2;
int counter =0;
    if(a1<x1||a2<x1)
        counter++;
    if(b1<y1||b2<y1)
        counter++;
    if(c1>z1||c2>z1)
        counter++;

    if(a1>x2||a2>x2)
        counter++;
    if(b1>y2||b2>y2)
        counter++;
    if(c1<z2||c2<z2)
        counter++;

    return (counter==6);
}

void Collider::RePosition() {

    //if(this->mesh==nullptr)
      //  std::cout<<"mesh in collider is null"<<std::endl;
    //if(this->mesh->model== nullptr)
        //std::cout<<"model in mesh is null"<<std::endl;
    glm::mat4 modalMatrix = (mesh->modalMatrix_mesh)*(mesh->model->modalMatrix) ;
    std::vector<glm::vec4> temp;
    temp.push_back(glm::vec4(0,0,0,1.f));
    temp.push_back(glm::vec4(0,0,0,1.f));
    for(int i=0;i<vertices.size();i++)
    {
        temp.push_back(glm::vec4(0,0,0,1.f));
        temp[i] = modalMatrix * vertices[i];
    }
   
    x1=std::max(temp[0].x,temp[1].x);
    y1=std::max(temp[0].y,temp[1].y);
    z1=std::max(temp[0].z,temp[1].z);
    x2=std::min(temp[1].x,temp[0].x);
    y2=std::min(temp[1].y,temp[0].y);
    z2=std::min(temp[1].z,temp[0].z);
    for(int i=0;i<temp.size();i++)
    {
        x1 = std::max(x1, temp[i].x);
        y1 = std::max(y1, temp[i].y);
        z1 = std::max(z1, temp[i].z);
        x2 = std::min(x2, temp[i].x);
        y2 = std::min(y2, temp[i].y);
        z2 = std::min(z2, temp[i].z);
    }

}
