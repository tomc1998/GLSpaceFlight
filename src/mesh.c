#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/cimport.h>        /* Plain-C interface     */
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>    /* Post processing flags */
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"

Mesh* load_mesh_from_ai_mesh(const struct aiMesh* ai_mesh) {
  printf("Num verts: %d\n", ai_mesh->mNumVertices);
  printf("Num faces: %d\n", ai_mesh->mNumFaces);

  /* Turn ai vertex data into a float array */
  float* verts = malloc(sizeof(float)*3*ai_mesh->mNumVertices);
  int ii = 0;
  for (; ii < ai_mesh->mNumVertices; ++ii) {
    verts[ii*3] = ai_mesh->mVertices[ii].x;
    verts[ii*3 + 1] = ai_mesh->mVertices[ii].y;
    verts[ii*3 + 2] = ai_mesh->mVertices[ii].z;
  }
  /* Turn ai face data into a uint array (vertex elements) */
  unsigned int *elements =
    (unsigned int*) malloc(sizeof(int) * ai_mesh->mNumFaces * 3);
  for(int i = 0; i < ai_mesh->mNumFaces; i ++) {
    elements[i * 3] = ai_mesh->mFaces[i].mIndices[0];
    elements[i * 3 + 1] = ai_mesh->mFaces[i].mIndices[1];
    elements[i * 3 + 2] = ai_mesh->mFaces[i].mIndices[2];
  }

  /* Create mesh */
  Mesh* m = (Mesh*)malloc(sizeof(Mesh));
  glGenVertexArrays(1, &(m->vao));
  glBindVertexArray(m->vao);
  m->num_vertices = ai_mesh->mNumVertices;
  m->num_elements = ai_mesh->mNumFaces * 3;
  /* Buffer vertex data */
  glGenBuffers(1, &(m->vbo));
  glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
  glBufferData(GL_ARRAY_BUFFER,
               ai_mesh->mNumVertices*3*sizeof(GLfloat),
               verts,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*)0);
  /* Buffer index data */
  glGenBuffers(1, &(m->e_buf));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->e_buf);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               ai_mesh->mNumFaces*3*sizeof(GLfloat),
               elements,
               GL_STATIC_DRAW);
  glBindVertexArray(0);
  return m;
}

const struct aiScene* load_ai_scene_from_file(const char* path) {
  return aiImportFile(path, 
                      aiProcess_CalcTangentSpace       |
                      aiProcess_Triangulate            |
                      aiProcess_JoinIdenticalVertices  |
                      aiProcess_SortByPType); 
}
