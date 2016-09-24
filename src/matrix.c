#include <assert.h>
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
  matrix[3] += x;
  matrix[7] += y;
  matrix[11] += z;
}

