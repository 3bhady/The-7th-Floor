#include "Mesh.h"
#include "Collider.h"
Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures,Model* parent)
{
this->vertices = vertices;
this->indices = indices;
this->textures = textures;
model=parent;
// Now that we have all the required data, set the vertex buffers and its attribute pointers.
this->setupMesh();

    Mesh * ptr=this;
    collider= new Collider(ptr);
    ptr = nullptr;
this->CalculateCollider();
}
void Mesh::CalculateCollider(){
    float x1=vertices[0].Position.x;
    float x2=vertices[0].Position.x;
    float y1=vertices[0].Position.y;
    float y2=vertices[0].Position.y;
    float z1=vertices[0].Position.z;
    float z2=vertices[0].Position.z;

    for(int i=0;i<vertices.size();i++)
    {
        x1=
                x1>vertices[i].Position.x?x1:vertices[i].Position.x;

        x2=
                x2<vertices[i].Position.x?x2:vertices[i].Position.x;

        y1=
                y1>vertices[i].Position.y?y1:vertices[i].Position.y;

        y2=
                y2<vertices[i].Position.y?y2:vertices[i].Position.y;

        z1=
                z1>vertices[i].Position.z?z1:vertices[i].Position.z;

        z2=
                z2<vertices[i].Position.z?z2:vertices[i].Position.z;

    }

  //  std::cout<<"max:"<<x1<<","<<y1<<","<<z1<<" |||"<<" min:";
    //     std::cout<<x2<<","<<y2<<","<<z2<<std::endl;

    collider->SetValues(x1,y1,z1,x2,y2,z2);

};
void Mesh::Draw(Shader* shader,glm::mat4 &modalMatrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(modalMatrix_mesh*modalMatrix));

    // Bind appropriate textures
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    GLuint normalNr = 1;
    GLuint heightNr = 1;
    for(GLuint i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
        // Retrieve texture number (the N in diffuse_textureN)
        stringstream ss;
        string number;
        string name = this->textures[i].type;
        if(name == "texture_diffuse")
            ss << diffuseNr++; // Transfer GLuint to stream
        else if(name == "texture_specular")
            ss << specularNr++; // Transfer GLuint to stream
        else if(name == "texture_normal")
            ss << normalNr++; // Transfer GLuint to stream
        else if(name == "texture_height")
            ss << heightNr++; // Transfer GLuint to stream
        number = ss.str();
        // Now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader->Program, (name + number).c_str()), i);
        // And finally bind the texture
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);

    }

    // Draw mesh
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Always good practice to set everything back to defaults once configured.
    for (GLuint i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}
void Mesh::setupMesh()
{
    // Create buffers/arrays
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
    // Vertex Tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));
    //  Vertex Bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
}

bool Mesh::IsCollide(Mesh  *mesh) {
    return collider->IsCollide(mesh->collider);
}

void Mesh::RePosition() {
    Mesh* ptr=this;
    collider->SetMech(ptr);
    ptr=NULL;
    collider->RePosition();

}

Mesh Mesh::CreateMeshInstanse(Model* p) {





    //cout<<"sadsad"<<endl;
    Mesh newMesh(this->vertices,this->indices,this->textures,p);
    Collider* tempColl=new Collider(&newMesh);
    int temp=collider->vertices.size();
    tempColl->SetValues(collider->vertices[0].x,collider->vertices[0].y,collider->vertices[0].z, collider->vertices[temp-1].x,collider->vertices[temp-1].y,collider->vertices[temp-1].z );
newMesh.collider=tempColl;
    newMesh.VAO=VAO;
    newMesh.modalMatrix_mesh =glm::mat4(1.0);

    tempColl= nullptr;
    delete tempColl;
    return newMesh;
}
/*
Mesh::Mesh( const Mesh &m) {
int temp=m.collider->vertices.size();
        collider=new Collider(this);
    collider->SetValues(m.collider->vertices[0].x,m.collider->vertices[0].y,m.collider->vertices[0].z, m.collider->vertices[temp-1].x,m.collider->vertices[temp-1].y,m.collider->vertices[temp-1].z );

     this->vertices=m.vertices;
    this->indices=m.indices;
    this-> textures=m.textures;
    this-> VAO=m.VAO;
     modalMatrix_mesh =glm::mat4(1.0);




}
*/