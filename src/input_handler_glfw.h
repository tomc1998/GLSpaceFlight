/**
    @file glfw_input_handler.h
    Contains functions to handler input events from GLFW.
    Must call set_input_handler_control_mapping() before this will
    handle any input.
*/

#ifndef INPUT_HANDLER_GLFW_H
#define INPUT_HANDLER_GLFW_H
#include <GLFW/glfw3.h>

struct Input_State;
typedef struct Input_State Input_State;

/**
   @struct Input_Control_Mapping_GLFW input_handler_glfw.h "input_handler_glfw.h" 
   @brief A mapping between GLFW input codes (i.e key codes) and controls (See Input_State)
*/
struct Input_Control_Mapping_GLFW {
  /** Number of mappings */
  int num_mappings;
  /** List of GLFW input or user-defined codes */
  int* inputs;
  /** List of pointers to control values to modify */
  int** controls;
};
typedef struct Input_Control_Mapping_GLFW Input_Control_Mapping_GLFW;

/**
    @fn void init_input_control_mapping_glfw(Input_Control_Mapping_GLFW* control_mapping)
    @brief Initialises a GLFW control mapping to default values.
    @param[out] control_mapping The control mapping to initialise.
    @param[in] input_state The input state
 */
void init_input_control_mapping_glfw(Input_Control_Mapping_GLFW*
                                     control_mapping,
                                     Input_State* input_state);

/**
    @fn void destroy_input_control_mapping_glfw(Input_Control_Mapping_GLFW* control_mapping)
    @brief Destroys resources held by an Input_Control_Mapping_GLFW.
    @param[out] control_mapping The control mapping to destroy.
 */
void destroy_input_control_mapping_glfw(Input_Control_Mapping_GLFW*
                                     control_mapping);


/**
   @fn void set_input_handler_control_mapping(Input_Control_Mapping_GLFW* control_mapping);
   @brief Sets the control mapping to use for this input handler
   @param[in] control_mapping The control mapping to use
   
   This must be called before any inputs are passed to input state.
*/
void set_input_handler_control_mapping(Input_Control_Mapping_GLFW*
                                       control_mapping);

void glfw_key_callback(GLFWwindow* w,
                       int key,
                       int scancode,
                       int action,
                       int mods);

#endif

