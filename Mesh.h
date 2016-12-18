#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

struct Vertex {
    // Position
    glm::vec3 Position;
    // Normal
    glm::vec3 Normal;
    // TexCoords
    glm::vec2 TexCoords;
    // Tangent
    glm::vec3 Tangent;
    // Bitangent
    glm::vec3 Bitangent;
};


struct Texture {
    GLuint id;
    string type;
    aiString path;
};

class Model;
class Collider;


class Mesh {
public:

    //mvp matrices
    //glm::mat4 modalMatrix = glm::mat4(1.0);
    glm::mat4 projectionMatrix_mesh;
    glm::mat4 viewMatrix_mesh;

    glm::mat4 rotationMatrix_mesh = glm::eulerAngleYXZ(1.0f, 0.0f, 0.0f);
    glm::mat4 translationMatrix_mesh = glm::translate(glm::mat4(), glm::vec3(0, 0,0.0f ));
    glm::mat4 scalingMatrix_mesh =glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
    //for test only
    //glm::vec4 forward= glm::vec4(0,0,1,1);
    glm::vec3 direction_mesh= glm::vec3(0,0,1);
    //right direction
    glm::vec3 right_mesh=glm::vec3(1,0,0);

    //position,scale,rotation
    glm::vec3 position_mesh= glm::vec3(0,0,0);

    glm::vec3 rotation_mesh= glm::vec3(0,0,0);
    glm::vec3 scaling_mesh= glm::vec3(0,0,0);
    glm::mat4 MVP_mesh;




//    Mesh( const Mesh& m);

    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    GLuint VAO;
    glm::mat4 modalMatrix_mesh =glm::mat4(1.0);
    Collider * collider;
    Model * model;
    bool IsTrigger=false;
    int tag;
    string Tag="z";
    /*  Functions  */
    // Constructor
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures,Model* parent);
   Mesh CreateMeshInstanse(Model* p);
    void CalculateCollider();
    // Render the mesh
    void Draw(Shader* shader,glm::mat4 &modalMatrix);
    bool IsCollide(Mesh *mesh);
    void RePosition();
    bool MoveTo(glm::vec3 target,GLfloat speed);
    void SetPosition(glm::vec3 pos,int type=0);
private:
    /*  Render data  */
    GLuint VBO, EBO;

    /*  Functions    */
    // Initializes all the buffer objects/arrays
    void setupMesh();
};



