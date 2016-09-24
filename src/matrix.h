/**
   @file matrix.h
   @brief Declares useful matrix functions.
 */

#ifndef MATRIX_H
#define MATRIX_H

/**
     Function to create a perspective projection matrix.
     @param[out] matrix The matrix to put the return data in. Caller allocated.
                        Should be space for 16 floats.
     @param[in] l The coordinate for the left edge on the near clipping plane.V
     @param[in] r The coordinate for the right edge on the near clipping plane.V
     @param[in] b The coordinate for the bottom edge on the near clipping plane.V
     @param[in] t The coordinate for the top edge on the near clipping plane.V
     @param[in] n The distance to the near-depth clipping plane (must be > 0)
     @param[in] f The distance to the far-depth clipping plane (must be > 0)
 */
void create_persp_proj_mat(float* matrix,
                           float l, float r,
                           float b, float t,
                           float n, float f);

/**
    Function to create a 4x4 identity matrix
    @param[out] matrix The matrix to put the return data in. Caller
                       allocated. Should be space for 16 floats.
 */
void create_mat4_identity(float* matrix);

/**
    Function to apply a 3D translation to a transformation matrix.
    @param[out] matrix The matrix to translate.
    @param[in] x Translation along the x axis.
    @param[in] y Translation along the y axis.
    @param[in] z Translation along the z axis.
 */
void apply_translation3f(float* matrix, const float x, const float y, const float z);

#endif
