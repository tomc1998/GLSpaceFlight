#include "game_state.h"
#include "input_state.h"

void update_game_state(Game_State* state, Input_State* input_state) {
  if (input_state->ctrl_dbg_quit) {
    state->endflag = 1;
  }
}

void init_game_state(Game_State* state,
                     const int screen_w,
                     const int screen_h) {
  state->screen_w = screen_w;
  state->screen_h = screen_h;
  state->endflag = 0;
}
                       

