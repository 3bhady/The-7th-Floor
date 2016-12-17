#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

// GL Includes
#ifndef gm
#define gm


#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <SOIL/SOIL.h>

#include <glm/gtx/euler_angles.hpp>

#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include"Script.h"

#include "GameManager.h"

#endif


class Collision;



using namespace glm;
//GLint TextureFromFile(const char* path, string directory, bool gamma = false);
GLint TextureFromFile(const char* path, string directory, bool gamma);
/*
 * kol Model feh model keda dh ele by7aded el transformation bta3o
 * lw 3ayz arsm el Model ba3ady 3ala kol mesh 3ndo w ab3tlo el model w kol mesh
 * feh mn gwah model tany by7aded el transformation bta3 el mesh relative l el Model el kber
 * w abl ma arsm el mesh dh ab3t l model ele hwa uniform mwgod f el shader 3lshan arsmo (y)
 */
class GameManager;
class Model
{
public:
    //testing ::

    //endtesting
    Model(bool gamma=false);
  glm::mat4 lastModalMatrix=glm::mat4(1.0);
    glm::vec3 lastPosition;
    glm::vec3 lastRotation;
    glm::vec3 lastDirection;
    glm::vec3 lastRight;
    /*  Model Data */
   static GameManager* gameManager;
    std::vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
    Script *script;

    Model* parent; //will be discussed may be unuseful ..
    vector<Model *>child;  //will be discussed may be unuseful ..

    bool IsTrigger;
    string Tag;
    bool IsAnimated=false;
    int FramesNumber=1; //cannot be less than 0 frames
    int CurrentFrame=0; //0 is the begining
   // static  vec3 lightPos ;

//mvp matrices
    glm::mat4 modalMatrix = glm::mat4(1.0);
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    glm::mat4 rotationMatrix = eulerAngleYXZ(1.0f, 0.0f, 0.0f);
    glm::mat4 translationMatrix = translate(mat4(), vec3(0, 0,0.0f ));
    glm::mat4 scalingMatrix =scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
    //for test only
    //glm::vec4 forward= glm::vec4(0,0,1,1);
    glm::vec3 direction= glm::vec3(0,0,1);
    //right direction
    glm::vec3 right=glm::vec3(1,0,0);

    //position,scale,rotation
    glm::vec3 position= glm::vec3(0,0,0);

    glm::vec3 rotation= glm::vec3(0,0,0);
    glm::vec3 scaling= glm::vec3(0,0,0);
    glm::mat4 MVP;

    /*  Functions   */
    // Constructor, expects a filepath to a 3D model.
    Model(string const & path,string tg, bool gamma = false);
    void Animate(bool state);
    // Draws the model, and thus all its meshes
    void Draw(Shader* shader);
private:


   /// static GameManager* gameManager; //pointer to gamemanager
    /*  Functions   */
    // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string path);

    // Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    // Checks all material textures of a given type and loads the textures if they're not loaded yet.
    // The required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
public:
    //translating the object to a certain position;

    void Rotate(float x,float y ,float z,float angle);
    void RotateAround(vec3 target,vec3 axis,float angle);
    void Scale(vec3 scal);
   // void SetLightPosition(float xpos,float ypos,float zpos);
    //setting up  rotation,translation ,scaling



    //move to another position
    bool MoveTo(vec3 target,GLfloat speed);


    void RePosition();
    void SetPosition(vec3 pos,int type=0);
    void SetRotation(vec3 rot,int type=0);
    void SetScaling(vec3 scal);
    void UpdateDirections();
    vector< pair<Mesh*,Mesh*> >* IsCollide(Model* model);

    //virtual??
    void OnCollision(Collision * collision);

    void AttachScript(Script* scr); //attach script for the model ..
    void Trigger(bool trigger);
    void AddChild(Model* Child);
    void AddParent(Model*Parent);
    Model* GetParent();
    Model* GetChild(int index);



};