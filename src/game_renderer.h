/**
   @file game_renderer.h
   @brief Contains code to render the game. 

   This file does not include code to render other screens such as
   menus, just the in game models and images.
*/

#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H
#include <GLFW/glfw3.h>

struct Game_State;

/**
   @brief Defines renderer settings.

   Call render_game() and pass this as a parameter to render using
   this renderer's settings.
   
   Does NOT contain data about the bounds of the game. This is contained in Game_State.
*/
struct Game_Renderer {
	GLuint vba, vbo;
};

/**
   @brief Typedef for convenience
 */
typedef struct Game_Renderer Game_Renderer;

/**
   @brief Initialises the game renderer.
   @param[out] game_renderer The renderer object to initialise. Caller allocated.
   @memberof Game_Renderer
   @public
*/
void init_game_renderer(Game_Renderer* game_renderer);

/**
   @brief Frees any resource owned by Game_Renderer
   @param[out] game_renderer The Game_Renderer object to destroy.
   @memberof Game_Renderer
   @public
*/
void destroy_game_renderer(Game_Renderer* game_renderer);

/**
   @brief Renders some game state.
   @param[in] renderer The Game_Renderer to use
   @param[in] s The Game_State to render.
   @memberof Game_Renderer
   @public
   
   Assumes that a GL context is current, and will render to whichever
   context is current.
   
   Bounds used based on Game_State::screen_w and Game_State::screen_h.
*/
void render_game(Game_Renderer* renderer, struct Game_State* s);

#endif
