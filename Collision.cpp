#include "Collision.h"
#include "Mesh.h"

Collision::Collision(Mesh * ownmesh,Mesh* mesh) {
    this->ownmesh=ownmesh;
    owncollider=ownmesh->collider;

    this->mesh=mesh;
    collider=mesh->collider;
    model=mesh->model;
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
