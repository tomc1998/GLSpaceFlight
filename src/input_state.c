#include "input_state.h"

void init_input_state(Input_State* input_state) {
  input_state->digital_input_state.ctrl_thrust = 0;
  input_state->digital_input_state.ctrl_brake = 0;
  input_state->digital_input_state.ctrl_dbg_quit = 0;
}

void destroy_input_state(Input_State* input_state) {
}


int get_num_controls() {
  return
    sizeof(Digital_Input_State)
    /sizeof(int)          /* Type used for key controls */
    /2;                   /* Key controls have a just_pressed variant too */
}

