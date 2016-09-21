#ifndef GAME_STATE_H
#define GAME_STATE_H

struct Input_State;
typedef struct Input_State Input_State;

/**
   @brief Holds all game state for running the game.

   Pass to Game_Renderer to render to the screen. The renderer will
   render at the dimensions specified by {@link screen_w} and {@link
   screen_h}.
*/
struct Game_State {
  /** The width in pixels of the game */
  int screen_w; 
  /** The height in pixels of the game */
  int screen_h; 
  /** Game loop runs when endflag == 0 */
  int endflag;
};
typedef struct Game_State Game_State;

/**
   @brief Initialises the game state.
   @param[out] state The state object to initialise. Caller allocated.
   @param[in] screen_w The width of the game screen in pixels.
   @param[in] screen_h The height of the game screen in pixels.
   @memberof Game_State
   @public
*/
void init_game_state(Game_State* state,
                     const int screen_w,
                     const int screen_h);

/**
   @brief Frees any resources owned by Game_State.
   @param[in] state The Game_State object to destroy.
   @memberof Game_State
   @public
*/
void destroy_game_state(Game_State* state);

/**
   @brief Updates the game state.
   @param[in] state The pointer to the game state to update.
   @param[in] input_state The pointer to the input state currently in use
   @memberof Game_State
   @public
*/
void update_game_state(Game_State* state, Input_State* input_state);

#endif


