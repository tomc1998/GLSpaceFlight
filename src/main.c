#include "game_state.h"
#include "input_state.h"
#include "input_handler_glfw.h"
#include "game_renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

/**
   @fn GLFWwindow* init_glfw(const char* title, int screen_w, int screen_h)
   @brief Initialises a GLFWwindow and returns a pointer to the window struct.
   @param title The title of the window.
   @param screen_w The width of the window.
   @param screen_h The height of the window.
   @return A pointer to the window struct created from glfwCreateWindow().

   Makes the window's GL context current for the thread running this function.
*/
GLFWwindow* init_glfw(const char* title, int screen_w, int screen_h) {
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(screen_w,
                                        screen_h,
                                        "Title",
                                        NULL,
                                        NULL);
  glfwMakeContextCurrent(window);
  return window;
}

/**
   Game entry point.
*/
int main(int argc, char** argv) {
  /* Create game state */
  Game_State* game_state = (Game_State*) malloc(sizeof(Game_State));
  init_game_state(game_state, 800, 600);
  /* Create game window */
  GLFWwindow* window = init_glfw("GLSpaceFlight", game_state->screen_w, game_state->screen_h);
  /* Create control mapping */
  Input_State* input_state = (Input_State*) malloc(sizeof(Input_State));
  init_input_state(input_state);
  Input_Control_Mapping_GLFW* control_mapping =
    (Input_Control_Mapping_GLFW*) malloc(sizeof(Input_Control_Mapping_GLFW));;
  init_input_control_mapping_glfw(control_mapping, input_state);

  set_input_handler_control_mapping(control_mapping);
  glfwSetKeyCallback(window, glfw_key_callback);

  while(!game_state->endflag) {
    update_game_state(game_state, input_state);
    render_game(game_state);
    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwWindowShouldClose(window)) {
      break;
    }
  }

  free(game_state);

  return 0;
}
