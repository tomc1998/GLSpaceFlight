#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "shader.h"
#include "matrix.h"
#include "game_state.h"
#include "game_renderer.h"

void init_game_renderer(Game_Renderer* game_renderer) {
  /* Test shaders */
  const char* v_shader = " \n \
#version 330 core \n \
uniform mat4 proj_mat; \n \
layout(location = 0) in vec3 vert; \n \
out vec3 col; \n \
void main() { \n \
gl_Position = proj_mat*vec4(vert + vec3(0, 0, -5), 1); \n \
col = vec3(0, 1-vert.z, vert.z+0.5); \n \
} \n \
  ";
  const char* f_shader = " \n \
#version 330 core \n \
out vec3 color; \n \
in vec3 col; \n \
void main(){ \n \
  color = col; \n \
} \n \
  ";

  /* Load test shader */
  game_renderer->test_shader_program =
    load_shader_program_from_src(v_shader,
                                 strlen(v_shader),
                                 f_shader,
                                 strlen(f_shader));
  glUseProgram(game_renderer->test_shader_program);

  /* Create a projection matrix */
  create_persp_proj_mat(&(game_renderer->proj_mat[0]), -1, 1, -1, 1, 2, 1000);

  /* Get uniform locations */
  game_renderer->shader_proj_mat_loc = /* Projection matrix */
    glGetUniformLocation(game_renderer->test_shader_program, "proj_mat");

  /* Load uniforms to GPU */
  glUniformMatrix4fv(game_renderer->shader_proj_mat_loc,
                     1,
                     GL_TRUE,
                     &(game_renderer->proj_mat[0]));

  /* Set up depth testing */
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void destroy_game_renderer(Game_Renderer* game_renderer) {
}

void render_mesh(Game_Renderer* game_renderer, Mesh* m) {
  glBindVertexArray(m->vao);
  glEnableVertexAttribArray(0);
  glDrawElements(GL_TRIANGLES,
                 m->num_elements,
                 GL_UNSIGNED_INT,
                 (void*)0);
  glDisableVertexAttribArray(0);
}

void render_game(Game_Renderer* game_renderer, Game_State* s) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render_mesh(game_renderer, game_renderer->test_mesh);
}


