#include <assimp/cimport.h>        /* Plain-C interface     */
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>    /* Post processing flags */
#include "mesh.h"

Mesh* load_mesh_from_ai_mesh(const struct aiMesh* ai_mesh) {
  return NULL;
}

const struct aiScene* load_ai_scene_from_file(const char* path) {
  return aiImportFile(path, 
                      aiProcess_CalcTangentSpace       |
                      aiProcess_Triangulate            |
                      aiProcess_JoinIdenticalVertices  |
                      aiProcess_SortByPType); 
}
