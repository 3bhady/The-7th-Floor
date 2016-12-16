#include "Collision.h"
#include "Mesh.h"
#include "Collider.h"
#include "Model.h"
class PlayerScript;

Collision::Collision(Mesh * ownmesh,Mesh* mesh) {
    this->ownmesh=ownmesh;
    owncollider=ownmesh->collider;

    this->mesh=mesh;
    collider=mesh->collider;
    model=mesh->model;
   // if(dynamic_cast<PlayerScript*>(ownmesh->model->script) != nullptr )
   // std::cout<<owncollider->x1<<":"<<owncollider->y1<<":"<<owncollider->z1<<"||"
   // << owncollider->x2<<":"<<owncollider->y2<<":"<<owncollider->z2<<std::endl;
}

Mesh *Collision::GetOwnMesh() {
    return ownmesh;
}

Mesh *Collision::GetMesh() {
    return mesh;
}

Model *Collision::GetModel() {
    return model;
}

Collider *Collision::GetOwnCollider() {
    return owncollider;
}

Collider *Collision::GetCollider() {
    return collider;
}
