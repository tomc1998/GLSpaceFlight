#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "shader.h"
#include "game_state.h"
#include "game_renderer.h"

void init_game_renderer(Game_Renderer* game_renderer) {
  /* Setup VAO */
  glGenVertexArrays(1, &(game_renderer->vao));
  glBindVertexArray(game_renderer->vao);
  float test_data[] = {
    0, 0, 1, 1, 0, 1, 1, 1, 1
  };
  glGenBuffers(1, &(game_renderer->vbo));
  glBindBuffer(GL_ARRAY_BUFFER, game_renderer->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(test_data), &(test_data[0]), GL_STATIC_DRAW);

  /* Load test shader */
  const char* v_shader = " \n \
#version 330 core \n \
layout(location = 0) in vec3 vert; \n \
void main() { \n \
gl_Position.xyz = vert; \n \
gl_Position.w = 1.0; \n \
} \n \
  ";
  const char* f_shader = " \n \
#version 330 core \n \
out vec3 color; \n \
void main(){ \n \
  color = vec3(1,0,0); \n \
} \n \
  ";
  game_renderer->test_shader_program =
    load_shader_program_from_src(v_shader,
                                 strlen(v_shader),
                                 f_shader,
                                 strlen(f_shader));
  glUseProgram(game_renderer->test_shader_program);
}

void destroy_game_renderer(Game_Renderer* game_renderer) {
}

void render_game(Game_Renderer* game_renderer, Game_State* s) {
  glBindVertexArray(game_renderer->vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, game_renderer->vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableVertexAttribArray(0);
}


