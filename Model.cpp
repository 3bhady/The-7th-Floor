#pragma once
#include "Model.h"
#include "GameManager.h"
#include "Collision.h"
 GameManager*Model:: gameManager= new GameManager();
//render text


//end rendering text




Model::Model(string const & path,string tag, bool gamma) : gammaCorrection(gamma)
        {this->Tag=tag;
                this->loadModel(path);
           this->script=new Script();//setting up the script component
            this->parent= nullptr;
            this->child.clear();

        }
Model::Model( bool gamma) : gammaCorrection(gamma)
{

    this->script=new Script();//setting up the script component
    this->parent=nullptr;
    this->child.clear();
}


void Model::Draw(Shader* shader)
{
/*
    int start =0;
int size = meshes.size();
int endframe =size/FramesNumber;

    if(IsAnimated==true)
    {
      //  std::cout<<" is Animated"<<std::endl;
        //std::cout<<size<<std::endl;

        start =CurrentFrame*endframe;
        size = start+endframe;
        endframe+= start;
        //std::cout<<CurrentFrame<<":"<<endframe<<std::endl;
        deltaTime+=gameManager->deltaTime;
        if(deltaTime>0.01f)
        {deltaTime=0;
        CurrentFrame++;}

        if(CurrentFrame>=FramesNumber)
            CurrentFrame=0;
    }
else
    { CurrentFrame=0; }
*/
  //  if(Tag=="player")
     //   std::cout<<meshes.size()<<std::endl;
int start =0;
    int size=meshes.size()/(FramesNumber*SpritesNumber);

if(IsAnimated)
{
    //start=CurrentFrame*CurrentSprite*size;
    start=CurrentSprite*FramesNumber*size;
    start*=CurrentFrame;
    size+=start;
    deltaTime+=gameManager->deltaTime;
    if(deltaTime>0.01f)
    {deltaTime=0;
        CurrentFrame++;}

    if(CurrentFrame>=SpritesNumber*FramesNumber)
        CurrentFrame=0;
}
    else
{
    CurrentFrame=0;
}
    for(GLuint i = start; i < size; i++)
    {
       /* if(Tag=="scene")
        {
            //std::cout<<meshes[i].Tag<<std::endl;
            if(meshes[i].Tag=="None_Door.bmp")
            {//meshes[i].IsTrigger=0;
                continue;}
            //this->meshes[71].Draw(shader,modalMatrix);
            //return;
        }*/
        this->meshes[i].Draw(shader,modalMatrix);
    }


}
void Model::loadModel(string path)
{
    // Read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // Check for errors
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // Retrieve the directory path of the filepath
    this->directory = path.substr(0, path.find_last_of('/'));

    // Process ASSIMP's root node recursively
    this->processNode(scene->mRootNode, scene);

}
void Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process each mesh located at the current node
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        // The node object only contains indices to index the actual objects in the scene.
        // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(this->processMesh(mesh, scene));
        meshes[i].tag=i;
    }
    // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(GLuint i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }

}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // Data to fill
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    // Walk through each of the mesh's vertices
    for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // Positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // Texture Coordinates
        if(mesh->mTextureCoords[0]) // Does the mesh coain texture coordinates?
        {
            glm::vec2 vec;
            // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        // Tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // Bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }
    // Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // Process materials
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // Diffuse: texture_diffuseN
        // Specular: texture_specularN
        // Normal: texture_normalN

        // 1. Diffuse maps
        vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. Specular maps
        vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. Normal maps
        std::vector<Texture> normalMaps = this->loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. Height maps
        std::vector<Texture> heightMaps = this->loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }

    // Return a mesh object created from the extracted mesh data
    Mesh * ptr = new Mesh(vertices, indices, textures,this);
    ptr->Tag=mesh->mName.C_Str();
    return *ptr;
}

void Model::AttachScript(Script* scr) //attach script for the model ..
{
    delete script;
    this->script=scr;
    scr->model=this;
}
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        GLboolean skip = false;
        for(GLuint j = 0; j < textures_loaded.size(); j++)
        {
            if(textures_loaded[j].path == str)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // If texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory,false);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}
void Model::Rotate(float x,float y ,float z,float angle){
    rotationMatrix=rotate(mat4(1.0f),glm::radians(angle), vec3(x, y,z ));
//rotation=vec3();
//  converting vec3 to vec4 because rotation matrix is 4d and we want to get forward

// storing rotation
    rotation=vec3(rotation.x+angle*x,rotation.y+angle*y,rotation.z+angle*z);

//updating forward and right directions
    UpdateDirections();
    modalMatrix=
            translate(mat4(), position)*rotationMatrix*translate(mat4(), -position)*modalMatrix;


}
void Model::Scale(vec3 scal){
    glm::mat4 scl=glm::scale(mat4(), scal);
    scaling+=scal;
    modalMatrix=
            translate(mat4(), position)*scl*translate(mat4(), -position)*modalMatrix;

}
/*void Model::SetLightPosition(float xpos,float ypos,float zpos){

    this->lightPos=glm::vec3(xpos,ypos,zpos);

}*/
//setting up  rotation,translation ,scaling

void Model::SetPosition(vec3 pos,int type){
  //  if(type==0)
   // lastPosition=position;


    translationMatrix=translate(mat4(), pos);

    modalMatrix=translationMatrix*translate(mat4(),-position)*modalMatrix;

    position=pos;

}

void Model::SetRotation(vec3 rot,int type){



// multiplying all rotations in order YXZ
    glm::mat4 newRotation=rotate(mat4(1.0f),glm::radians(rot.z), vec3(0, 0,1 ))*rotate(mat4(),glm::radians(rot.x), vec3(1,0,0 ))*rotate(mat4(),glm::radians(rot.y), vec3(0, 1,0 ));
    glm::mat4 reverseOldRotation=rotate(mat4(1.0f),glm::radians(-rotation.y), vec3(0, 1,0 ))*rotate(mat4(),glm::radians(-rotation.x), vec3(1,0,0 ))*rotate(mat4(),glm::radians(-rotation.z), vec3(0, 0,1 ));
    rotationMatrix=newRotation*reverseOldRotation;
    modalMatrix=
            translate(mat4(), position)*rotationMatrix*translate(mat4(), -position)*modalMatrix;
//update forward and right directions
    UpdateDirections();
    rotation=rot;
}
void Model::SetScaling(vec3 scal){
    glm::mat4 scalMatrixTemp= glm::scale(mat4(),-scaling);
    scalingMatrix=glm::scale(mat4(), scal);

    scaling=scal;
    modalMatrix=
            translate(mat4(), position)*scalingMatrix*scalMatrixTemp*translate(mat4(), -position)*modalMatrix;


}

void Model::UpdateDirections(){
    vec4 directionTemp=vec4(direction,1);
    directionTemp=rotationMatrix*directionTemp;
    //directionTemp=glm::normalize(directionTemp);
    direction=vec3(directionTemp.x,directionTemp.y,directionTemp.z);
    direction=glm::normalize(direction);
//setting up right vector
    right=glm::cross(direction,vec3(0,1,0));
    right=glm::normalize(right);
}

vector< pair<Mesh*,Mesh*> >* Model::IsCollide(Model* model) {
    //this complicated vector pointer has the pair of meshes which collided together
    //they're returned to game manager so that he can create a collision object and send it to each model
    vector< pair<Mesh*,Mesh*> >* vec=new vector< pair<Mesh*,Mesh*> >;//= new vector<pair<Mesh*,Mesh*> >;
    for(int i=0;i<meshes.size();i++)
    {
        if(meshes[i].IsTrigger==0)
            continue;
        for(int j=0;j<model->meshes.size();j++)
        {
            if(model->meshes[j].IsTrigger==0)
                continue;
            if(meshes[i].IsCollide( &(model->meshes[j]) )
                ||model->meshes[j].IsCollide( &(meshes[i]) ) )
            vec->push_back( make_pair(&meshes[i],&(model->meshes[j])) );
        }
    }
    return vec; //first is ownMesh second is mesh
}

void Model::OnCollision(Collision * collision) {
//this is implemented by the classes which derive Model class
    //for testing only now
this->script->OnCollision(collision);
    //std::cout<<"OnCollision is called now"<<std::endl;
    //delete collision;

}

void Model::Trigger(bool trigger) {
for(int i=0;i<meshes.size();i++)
    meshes[i].IsTrigger=trigger;
    IsTrigger=trigger;
}

void Model::RePosition() {
    for (int i = 0; i <meshes.size() ; ++i) {
        meshes[i].RePosition();
    }
}

extern GLint TextureFromFile(const char* path, string directory, bool gamma= false)
{
    //Generate texture ID and load texture data
    string filename = string(path);
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, gamma ? GL_SRGB : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;

}
bool Model::MoveTo(vec3 target,GLfloat speed){
    //check collision , should check  if position =target
    bool shouldReturn =true;
    double xDifference=abs((target.x-position.x));
    double yDifference=abs((target.y-position.y));
    double zDifference=abs((target.z-position.z));
    if((xDifference>=0&&xDifference<=0.19)&&(yDifference>=0&&yDifference<=0.19)&&(zDifference>=0&&zDifference<=0.19) ){
        this->SetPosition(target);
       // std::cout<<" reached the target pos"<<std::endl;
        return true;}


    //cout << position.x << " " << position.y << " " <<position.z << " "<<endl;
    vec3 nextPosition= target*speed+position*(1.f-speed);

    SetPosition(nextPosition);
    return false;


}

void Model::RotateAround(vec3 target,vec3 axis, float angle) {

    rotationMatrix=rotate(mat4(),glm::radians(angle), axis);
//rotation=vec3();
//  converting vec3 to vec4 because rotation matrix is 4d and we want to get forward

// storing rotationbool IsAnimated=false;
 //   rotation=vec3(rotation.x+angle*axis.x,rotation.y+angle*axis.y,rotation.z+angle*rotation.z);

//updating forward and right directions
    UpdateDirections();
    modalMatrix=
            translate(mat4(), target)*rotationMatrix*translate(mat4(), -target)*modalMatrix;
    vec4 posTemp=vec4(position.x,position.y,position.z,1.f);
    posTemp=rotationMatrix*posTemp;
    position=vec3(posTemp.x,posTemp.y,posTemp.z);

}

void Model::Animate(bool state) {
//this->IsAnimated=state;
}

void Model::AddChild(Model *Child) {
Child->parent=this;
    this->child.push_back(Child);
    Child->parent=this;
}

void Model::AddParent(Model *Parent) {
this->parent=Parent;
    Model* temp=this;
    Parent->child.push_back(temp);
}

Model *Model::GetChild(int index) {
    return child[index];
}

Model *Model::GetParent() {
    return parent;
}

void Model::Destroy() {
for(int i=0; i<gameManager->gameModel.size(); i++)
{
    if(gameManager->gameModel[i]==this)
    {
        gameManager->gameModel.erase(gameManager->gameModel.begin()+i);

    }
}
}

