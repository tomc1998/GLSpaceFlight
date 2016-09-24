/**
   @file mesh.h
   @brief Contains methods to load and render meshes
 */

#ifndef MESH_H
#define MESH_H
#include <GLFW/glfw3.h>

struct aiMesh;
struct aiScene;

/**
   @brief Stores vbo and vao IDs buffered with data to draw the mesh.
 */
struct Mesh {
  /** Vertex buffer */
  GLuint v_buf;
  /** Normal buffer */
  GLuint n_buf;
  /** Index buffer */
  GLuint i_buf;
  /** Vertex array object for this mesh */
  GLuint vao;

  unsigned num_vertices;
  unsigned num_indices;
};
/**
   @brief Typedef for convenience
 */
typedef struct Mesh Mesh;

/**
   @brief Loads an assimp mesh into VBOs, then returns the Mesh struct.
   @param[in] ai_mesh The assimp mesh to load.
   @return The Mesh containing vbos storing the mesh's data.
   @memberof Mesh
   @public
 */
Mesh* load_mesh_from_ai_mesh(const struct aiMesh* ai_mesh);

/**
   @brief Loads an assimp aiScene from a given file path.
   @param[in] path The path of the aiScene to load.
   @return The aiScene loaded from the file.
 */
const struct aiScene* load_ai_scene_from_file(const char* path);


#endif
