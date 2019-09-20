#ifndef VECTORUTIL_HPP
#define VECTORUTIL_HPP
#define SWAP_ROWS_DOUBLE(a, b) { double *_tmp = a; (a) = (b); (b) = _tmp; }
#define SWAP_ROWS_FLOAT(a, b) { float *_tmp = a; (a) = (b); (b) = _tmp; }
#define MAT(m, r, c) (m)[(c) * 4 + (r)]

#include "libs.hpp"
using namespace glm;

float interpolation(double x, int actualW, int actualH, int appW, int appH);
mat4 doubleArrayToMat4(GLdouble arr[]);
void printVector(vec3 vec, std::string name);
void printArray(float floats[]);
void printArray(GLint doubles[]);
void printMatrix(mat4 mat, std::string name);
int glhProjectf(float objx, float objy, float objz, GLdouble *modelview, GLdouble *projection, int *viewport, float *windowCoordinate);
void MultiplyMatrices4by4OpenGL_FLOAT(float *result, float *matrix1, float *matrix2);
void MultiplyMatrixByVector4by4OpenGL_FLOAT(float *resultvector, const float *matrix, const float *pvector);
int glhInvertMatrixf2(float *m, float *out);
#endif

