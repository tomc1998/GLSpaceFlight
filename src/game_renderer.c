#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "shader.h"
#include "matrix.h"
#include "game_state.h"
#include "game_renderer.h"

void init_game_renderer(Game_Renderer* game_renderer) {
  /* VBO Test data */
  float test_data[] = {
    0, 0, -5, 1, 0, -5, 1, 1, -5
  };

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

  /* Setup VAO */
  glGenVertexArrays(1, &(game_renderer->vao));
  glBindVertexArray(game_renderer->vao);
  glGenBuffers(1, &(game_renderer->vbo));
  glBindBuffer(GL_ARRAY_BUFFER, game_renderer->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(test_data), &(test_data[0]), GL_STATIC_DRAW);

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

  /* Set up depth testing */
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

}

void destroy_game_renderer(Game_Renderer* game_renderer) {
}

void render_game(Game_Renderer* game_renderer, Game_State* s) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUniformMatrix4fv(game_renderer->shader_proj_mat_loc,
                     1,
                     GL_TRUE,
                     &(game_renderer->proj_mat[0]));
  /*glBindVertexArray(game_renderer->vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, game_renderer->vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0); */

  glBindVertexArray(game_renderer->test_mesh->vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, game_renderer->test_mesh->v_buf);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
               game_renderer->test_mesh->i_buf);
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        0,
                        (void*)0);
  glDrawElements(GL_TRIANGLES,
                 game_renderer->test_mesh->num_indices,
                 GL_UNSIGNED_INT,
                 (void*)0);
  glDisableVertexAttribArray(0);
  
}


