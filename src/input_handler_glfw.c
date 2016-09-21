#include "input_handler_glfw.h"
#include "input_state.h"
#include <stdlib.h>

/** The control mapping to use for this input handler */
static Input_Control_Mapping_GLFW* control_mapping;

void init_input_control_mapping_glfw(Input_Control_Mapping_GLFW*
                                     control_mapping,
                                     Input_State* input_state) {
  /* Figure out the size of memory to allocate for inputs and
  controls*/
  control_mapping->num_mappings = get_num_controls();
  const size_t size_to_alloc_inputs =
    control_mapping->num_mappings*sizeof(int);
  const size_t size_to_alloc_controls =
    control_mapping->num_mappings*sizeof(int*);

  /* Allocate memory */
  control_mapping->inputs =
    (int*) malloc(size_to_alloc_inputs);
  control_mapping->controls =
    (int**) malloc(size_to_alloc_controls);

  /* Set default controls */
  control_mapping->inputs[0] = GLFW_KEY_W;
  control_mapping->inputs[1] = GLFW_KEY_S;
  control_mapping->inputs[2] = GLFW_KEY_ESCAPE;
  control_mapping->controls[0] = &(input_state->ctrl_thrust);
  control_mapping->controls[1] = &(input_state->ctrl_brake);
  control_mapping->controls[2] = &(input_state->ctrl_dbg_quit);
}

void destroy_input_control_mapping_glfw(Input_Control_Mapping_GLFW*
                                     control_mapping) {
  free(control_mapping->inputs);
  free(control_mapping->controls);
}

void set_input_handler_control_mapping(Input_Control_Mapping_GLFW*
                                       _control_mapping) {
  control_mapping = _control_mapping;
}

void glfw_key_callback(GLFWwindow* w,
                       int key,
                       int scancode,
                       int action,
                       int mods) {
  /* Loop through inputs, find the respective control */
  int ii = 0;
  for (; ii < control_mapping->num_controls; ++ii) {
    if (control_mapping->inputs[ii] == key) {
      int* control = control_mapping->controls[ii];
      if (action == GLFW_PRESS) {
        if (*control == 0) {
          *(control + 1) = 1; // Set just pressed
        }
        *control = 1; // Set control state
      }
      else {
        *control = 0;
        *(control+1) = 0;
      }
      break;
    }
  }
}
