#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game_state.h"
#include "input_state.h"
#include "input_handler_glfw.h"
#include "game_renderer.h"

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
  GLFWwindow* window = NULL;
  /* Init GLFW */
  glfwInit();
  /* Set GLFW to try and use OpenGL 3.3 */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  /* We need this! This will stop us using deprecated functionality, and the */
  /* mesa drivers on linux only support GL 3.3 core profile, not compatibility! */
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(screen_w, screen_h,
                            "Title",
                            NULL, NULL);
  /* Set current context to be the window we just created, allows GL functions */
  /* to affect this window's frame */
  glfwMakeContextCurrent(window);

  /* Load OpenGL extensions with GLAD */
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    printf("Can't load OpenGL extensions\n");
  }
  printf("OpenGL Ver - %d.%d\n", GLVersion.major, GLVersion.minor);

  return window;
}

/**
   Game entry point.
*/
int main(int argc, char** argv) {
  Game_State* game_state = NULL;
  Game_Renderer* game_renderer = NULL;
  GLFWwindow* window = NULL;
  Input_State* input_state = NULL;
  Input_Control_Mapping_GLFW* control_mapping = NULL;

  /* Create game state */
  game_state = (Game_State*) malloc(sizeof(Game_State));
  init_game_state(game_state, 800, 600);
  /* Create game window */
  window = init_glfw("GLSpaceFlight", game_state->screen_w, game_state->screen_h);
  /* Create control mapping */
  input_state = (Input_State*) malloc(sizeof(Input_State));
  init_input_state(input_state);
  control_mapping =
    (Input_Control_Mapping_GLFW*) malloc(sizeof(Input_Control_Mapping_GLFW));
  init_input_control_mapping_glfw(control_mapping, input_state);
  /* Create game renderer */
  game_renderer = (Game_Renderer*) malloc(sizeof(Game_Renderer));
  init_game_renderer(game_renderer);

  /* Set up input handler and assign key callbacks */
  set_input_handler_control_mapping(control_mapping);
  glfwSetKeyCallback(window, glfw_key_callback);

  while(!game_state->endflag) {
    /* Update game state */
    update_game_state(game_state, input_state);
    /* Render game */
    render_game(game_renderer, game_state);
    /* Flip buffers, poll events */
    glfwSwapBuffers(window);
    glfwPollEvents();
    /* If window should close, exit game loop */
    if (glfwWindowShouldClose(window)) {
      break;
    }
  }

  destroy_game_state(game_state);
  free(game_state);
  destroy_input_control_mapping_glfw(control_mapping);
  free(control_mapping);
  destroy_input_state(input_state);
  free(input_state);
  destroy_game_renderer(game_renderer);
  free(game_renderer);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
