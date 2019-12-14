#ifndef MODEL_H
#define MODEL_H
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <soil/src/SOIL.h>

#include "Mesh.h"

GLint TextureFromFile(const char* path, string directory);

class Model
{
public:
    Model(GLchar* path);
    void Render(Shader shader);
private:
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;
    //FUNCTIONS
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

#endif


