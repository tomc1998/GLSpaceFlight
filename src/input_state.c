#include "input_state.h"

void init_input_state(Input_State* input_state) {
  input_state->ctrl_thrust = 0;
  input_state->ctrl_brake = 0;
  input_state->ctrl_dbg_quit = 0;
}

int get_num_controls() {
  return
    sizeof(Input_State)
    /sizeof(int)          /* Type used for controls */
    /2;                   /* Controls have a just_pressed variant too */
}

