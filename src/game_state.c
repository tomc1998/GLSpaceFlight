#include <stdio.h>
#include "game_state.h"
#include "input_state.h"

void update_game_state(Game_State* state, Input_State* input_state) {
  if (input_state->digital_input_state.ctrl_dbg_quit) {
    state->endflag = 1;
  }
  
  if (input_state->digital_input_state.ctrl_fwd) {
    state->cam_pos.z -= 0.02f;
  }
  if (input_state->digital_input_state.ctrl_bkwd) {
    state->cam_pos.z += 0.02f;
  }
  if (input_state->digital_input_state.ctrl_right) {
    state->cam_pos.x += 0.02f;
  }
  if (input_state->digital_input_state.ctrl_left) {
    state->cam_pos.x -= 0.02f;
  }
  if (input_state->digital_input_state.ctrl_up) {
    state->cam_pos.y += 0.02f;
  }
  if (input_state->digital_input_state.ctrl_down) {
    state->cam_pos.y -= 0.02f;
  }
}

void init_game_state(Game_State* state,
                     const int screen_w,
                     const int screen_h) {
  state->screen_w = screen_w;
  state->screen_h = screen_h;
  state->endflag = 0;
}
                       
void destroy_game_state(Game_State* state) {
}

