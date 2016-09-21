#ifndef INPUT_STATE_H
#define INPUT_STATE_H

/**
   @struct Input_State input_state.h "input_state.h"
   @brief Contains state of controls, i.e whether the jump button is
          pressed.
          
   Updated by an input handler (glfw_input_handler.h for
   example).

   All fields must be ints, as this fact is used to to allocate memory
   in other places (see get_num_controls()).

   All fields must also be followed by a 'just_pressed' modifier int flag.
 */
struct Input_State {
  /** Activate ship thrusters when down */
  int ctrl_thrust;
  /** True when control has just been pressed (rather than held) */
  int ctrl_thrust_just_pressed;

  /** Activate ship brakes when down */
  int ctrl_brake;
  /** True when control has just been pressed (rather than held) */
  int ctrl_brake_just_pressed;

  /** Quick exit game for debug */
  int ctrl_dbg_quit;
  /** True when control has just been pressed (rather than held) */
  int ctrl_dbg_quit_just_pressed;
};
typedef struct Input_State Input_State;

/**
   @fn void init_input_state(Input_State* input_state)
   @brief Initialises input_state control values to their defaults.
   @param[out] input_state The input_state to modify. Caller allocated.
   @memberof Input_State
   @public
 */
void init_input_state(Input_State* input_state);

/**
   @fn get_num_controls()
   @brief Gets the number of controls in the input state.
   @return The number of controls used in Input_State
   
   Uses the struct Input_State and sizeof() to get a result. 

   *Assumptions*

   - Input_State controls all use the 'int' type.
   - Input_State controls also contain a 'just_pressed' int flag which
     indicates whether the control has just been pressed or not.
*/
int get_num_controls();

#endif 
