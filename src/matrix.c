#include <assert.h>
#include <string.h>
#include "vector.h"
#include "matrix.h"

void create_persp_proj_mat(float* matrix,
                           float l, float r,
                           float b, float t,
                           float n, float f) {
  assert(n > 0);
  assert(f > 0);

  matrix[0] = 2*n/(r-l);
  matrix[1] = 0;
  matrix[2] = (r+l)/(r-l);
  matrix[3] = 0;

  matrix[4] = 0;
  matrix[5] = 2*n/(t-b);
  matrix[6] = (t+b)/(t-b);
  matrix[7] = 0;

  matrix[8] = 0;
  matrix[9] = 0;
  matrix[10] = -(f+n)/(f-n);
  matrix[11] = -2*f*n/(f-n);

  matrix[12] = 0;
  matrix[13] = 0;
  matrix[14] = -1;
  matrix[15] = 0;
}

void create_mat4_identity(float* matrix) {
  matrix[0] = 1;
  matrix[1] = 0;
  matrix[2] = 0;
  matrix[3] = 0;

  matrix[4] = 0;
  matrix[5] = 1;
  matrix[6] = 0;
  matrix[7] = 0;

  matrix[8] = 0;
  matrix[9] = 0;
  matrix[10] = 1;
  matrix[11] = 0;

  matrix[12] = 0;
  matrix[13] = 0;
  matrix[14] = 0;
  matrix[15] = 1;
}

void apply_translation3f(float* matrix, const float x, const float y, const float z) {
  matrix[12] += x;
  matrix[13] += y;
  matrix[14] += z;
}

/* Just copying gluLookAt impl */
void mat4_view_lookat(float* matrix, 
                      const vec3f* eye,
                      const vec3f* centre,
                      const vec3f* up_vec) {
  vec3f forward, side, up;
  /* matrix (param) is copied to this */
  float in_mat[16]; 
  /* Holds the transformation, which the matrix param is multiplied by. */
  float transform[16]; 

  forward.x = centre->x - eye->x;
  forward.y = centre->y - eye->y;
  forward.z = centre->z - eye->z;
  vec3fnor(&forward);

  /* Side = forward x up */
  vec3fcross(&side, &forward, up_vec);
  vec3fnor(&side);

  /* Recompute up as: up = side x forward */
  vec3fcross(&up, &side, &forward);
  vec3fnor(&up);

  /* Create an identity matrix */
  /* Fill this identity matrix with the transformation */
  transform[0] = side.x;
  transform[4] = side.y;
  transform[8] = side.z;

  transform[1] = up.x;
  transform[5] = up.y;
  transform[9] = up.z;

  transform[2]  = -forward.x;
  transform[6]  = -forward.y;
  transform[10] = -forward.z;
  transform[3] = transform[7] = transform[11] = 0;

  transform[15] = 1;

  /* transform[12] = 0; */
  /* transform[13] = 0; */
  /* transform[14] = 0; */
  transform[12] = -vec3fdot(&side, eye);
  transform[13] = -vec3fdot(&up, eye);
  transform[14] = vec3fdot(&forward, eye);
  
  /* Multiply the in matrix by this one */
  memcpy(in_mat, matrix, sizeof(float)*16);
  mat4_mult_mat4(matrix, transform, in_mat);
  /* apply_translation3f(matrix, -eye->x, -eye->y, -eye->z); */
}

/* Potentially slow, but unless we find a bottleneck with matrix
   multiplication, rather concise. */
void mat4_mult_mat4(float* dest, const float* a, const float* b){
  unsigned ii;
  unsigned jj;
  for (ii = 0; ii < 4; ++ii) {
    for (jj = 0; jj < 4; ++jj) {
      dest[ii*4+jj] = 
        a[ii*4]*b[jj] 
        + a[ii*4+1]*b[jj+4] 
        + a[ii*4+2]*b[jj+8] 
        + a[ii*4+3]*b[jj+12];
    }
  }
}
