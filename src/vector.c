#include <math.h>

#include "vector.h"

void init_vec3f(vec3f* v, float x, float y, float z) {
  v->x = x;
  v->y = y;
  v->z = z;
}

float vec3fdot(const vec3f* a, const vec3f* b) {
  return a->x*b->x + a->y*b->y + a->z*b->z;
}

void vec3fcross(vec3f* dest, const vec3f* a, const vec3f* b) {
  dest->x = a->y*b->z - a->z*b->y;
  dest->y = a->z*b->x - a->x*b->z;
  dest->z = a->x*b->y - a->y*b->x;
}

void vec3fnor(vec3f* a) {
  float len = vec3flen(a);
  if (len == 0) {return;}
  a->x = a->x / len;
  a->y = a->y / len;
  a->z = a->z / len;
}

float vec3flen(const vec3f* a) {
  return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}
