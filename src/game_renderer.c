#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "shader.h"
#include "matrix.h"
#include "vector.h"
#include "game_state.h"
#include "game_renderer.h"

void init_game_renderer(Game_Renderer* game_renderer, Game_State* s) {
  float ratio; 
  float fov; 
  float top; 
  float bottom; 
  float left; 
  float right; 
  /* Can't use 'near' and 'far' on MSVC, reserved keywords */
  float n = 1;
  float f = 100;
  /* Test shaders */
  const char* v_shader = " \n \
#version 330 core \n \
uniform mat4 proj_mat; \n \
uniform mat4 view_mat; \n \
layout(location = 0) in vec3 vert; \n \
out vec3 col; \n \
void main() { \n \
vec4 trans_pos = proj_mat*view_mat*vec4(vert, 1); \n \
gl_Position = trans_pos; \n \
col = vec3(0, 1-trans_pos.z, trans_pos.z+0.5); \n \
} \n ";
  const char* f_shader = " \n \
#version 330 core \n \
out vec3 color; \n \
in vec3 col; \n \
void main(){ \n \
  color = col; \n \
} \n ";

  /* Load test shader */
  game_renderer->test_shader_program =
    load_shader_program_from_src(v_shader,
                                 strlen(v_shader),
                                 f_shader,
                                 strlen(f_shader));
  glUseProgram(game_renderer->test_shader_program);

  /* Create a projection matrix */
  ratio = (float)s->screen_w/(float)s->screen_h;
  fov = 45; 
  top = (float) (-tan(fov * 3.141f / 360.0f) * n);
  bottom = -top;
  left = ratio * top;
  right = ratio * bottom;
  create_persp_proj_mat(&(game_renderer->proj_mat[0]), left, right, top, bottom, n, f);
  /* Set initial camera position */
  init_vec3f(&s->cam_pos, 0, 0, 5);

  /* Get uniform locations */
  game_renderer->shader_proj_mat_loc = /* Projection matrix */
    glGetUniformLocation(game_renderer->test_shader_program, "proj_mat");
  game_renderer->shader_view_mat_loc = /* View matrix */
    glGetUniformLocation(game_renderer->test_shader_program, "view_mat");

  /* Load uniforms to GPU */
  glUniformMatrix4fv(game_renderer->shader_proj_mat_loc,
                     1,
                     GL_FALSE,
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
  vec3f centre;
  vec3f up;
  init_vec3f(&centre, 0, 0, 0);
  init_vec3f(&up, 0, 1, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  /* Update view mat */
  create_mat4_identity(&(game_renderer->view_mat[0]));
  mat4_view_lookat(&(game_renderer->view_mat[0]),
                   &s->cam_pos,
                   &centre,
                   &up);
                   
  glUniformMatrix4fv(game_renderer->shader_view_mat_loc,
                     1,
                     GL_FALSE,
                     &(game_renderer->view_mat[0]));

  render_mesh(game_renderer, game_renderer->test_mesh);
}


