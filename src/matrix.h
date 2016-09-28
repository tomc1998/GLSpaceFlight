/**
   @file matrix.h
   @brief Declares useful matrix functions.
*/

#ifndef MATRIX_H
#define MATRIX_H

struct vec3f;

/**
   @brief Function to create a perspective projection matrix.
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
   @brief Function to create a 4x4 identity matrix
   @param[out] matrix The matrix to put the return data in. Caller
   allocated. Should be space for 16 floats.
*/
void create_mat4_identity(float* matrix);

/**
   @brief Function to apply a 3D translation to a transformation matrix.
   @param[out] matrix The matrix to translate.
   @param[in] x Translation along the x axis.
   @param[in] y Translation along the y axis.
   @param[in] z Translation along the z axis.
*/
void apply_translation3f(float* matrix, const float x, const float y, const float z);

/**
   @brief Function to create a view matrix given a camera position, and a
   world position to look at. Works just like gluLookAt.
   @param[in,out] matrix The float array to multiply the matrix data by. Caller 
   allocated. Should be space for 16 floats.
   @param[in] x X position of camera in world space.
   @param[in] y Y position of camera in world space.
   @param[in] z Z position of camera in world space.
   @param[in] cx X position of the place to look at in world space.
   @param[in] cy Y position of the place to look at in world space.
   @param[in] cz Z position of the place to look at in world space.
   @param[in] ux X part of the up vector.
   @param[in] uy Y part of the up vector.
   @param[in] uz Z part of the up vector.
   
   This function will multiply the param matrix by the one created
   with the other parameters, so make sure the in matrix is valid. Use
   create_mat4_identity() for an identity matrix.
*/
void mat4_view_lookat(float* matrix, 
                      const struct vec3f* eye,
                      const struct vec3f* centre,
                      const struct vec3f* up_vec);

/**
   @brief Multiplies 2 4D matrices together - a * b.
   @param[out] dest The destination for the multiplication.
   @param[in] a The matrix to be multiplied. The one on the left.
   @param[in] b The matrix to be multiplied. The one on the right.
   
   Note: Make sure the dest matrix does not equal either a or
   b. Create a copy for this.
*/
void mat4_mult_mat4(float* dest, const float* a, const float* b);

#endif
