/**
   @file vector.h
   @brief Defines structs and functions relating to vectors
 */
#ifndef VECTOR_H
#define VECTOR_H

/**
   @brief Struct representing a 3D vector.
*/
struct vec3f {
  float x, y, z;
};
/**
   @brief Typedef for convenience 
*/
typedef struct vec3f vec3f;

/**
   @brief Initialises a vec3f with the given values
   @param[out] v The vec3f to initialise
   @param[in] x The x coordinate of the vector
   @param[in] y The y coordinate of the vector
   @param[in] z The z coordinate of the vector
   @public
   @memberof vec3f
*/
void init_vec3f(vec3f* v, float x, float y, float z);

/**
   @brief Applies the dot product a . b
   @param a[in] A pointer to the first vector.
   @param b[in] A pointer to the second vector.
   @public
   @memberof vec3f

   @return The dot product a . b.
*/
float vec3fdot(const vec3f* a, const vec3f* b);

/**
   @brief Applies the cross product a x b
   @param[out] dest The result of the cross product operation on a and b.
   @param[in] a A pointer to the first vector.
   @param[in] b A pointer to the second vector.
   @public
   @memberof vec3f
   
   Note: Param dest is caller allocated.
*/
void vec3fcross(vec3f* dest, const vec3f* a, const vec3f* b);

/**
   @brief Normalises a vector
   @param[in,out] a The vector to normalise.
   @public
   @memberof vec3f

   Note: This functionw will modify param a.
*/
void vec3fnor(vec3f* a);


/**
   @brief Calculated the vector length using pythagoras.
   @param[in] a The vec3f to calculate the length of.
   @return The length of param a.
   @public
   @memberof vec3f
*/
float vec3flen(const vec3f* a);

/**
   @brief Calculated the vector length using pythagoras.
   @param[in] a The vec3f to calculate the length of.
   @return The length of param a.
   @public
   @memberof vec3f
*/
float vec3flen2(const vec3f* a);

#endif
