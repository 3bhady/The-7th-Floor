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
    /*  Functions  */
    // Constructor
    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures,Model* parent);

    void CalculateCollider();
    // Render the mesh
    void Draw(Shader* shader,glm::mat4 &modalMatrix);
    bool IsCollide(Mesh *mesh);
    void RePosition();
private:
    /*  Render data  */
    GLuint VBO, EBO;

    /*  Functions    */
    // Initializes all the buffer objects/arrays
    void setupMesh();
};



