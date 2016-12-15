#pragma once
class Mesh;
class Collider;
class Model;
class Collision {
private:
    Mesh * ownmesh, *mesh;
    Collider * owncollider,*collider;
    Model * model;
public:
    Collision(Mesh * ownmesh,Mesh*  mesh);
    Mesh* GetOwnMesh();
    Mesh* GetMesh();
    Model* GetModel();
    Collider* GetOwnCollider();
    Collider* GetCollider();
};
