#ifndef MATRIX3F_H
#define MATRIX3F_H

#include "./include/debug.h"

#include "./include/vector3f.h"

typedef struct {
    float A11, A12, A13;
    float A21, A22, A23;
    float A31, A32, A33;
} Matrix3f;

// Initialize a zero matrix
void initMatrix3fZero(Matrix3f *m);

// Initialize a matrix with rows as Vector3f
void initMatrix3fWithRows(Matrix3f *m, const Vector3f *row1, const Vector3f *row2, const Vector3f *row3);

// Initialize a matrix with values
void initMatrix3fWithValues(Matrix3f *m, float A11, float A12, float A13,
                             float A21, float A22, float A23,
                             float A31, float A32, float A33);

// Matrix multiplication with a Vector3f
Vector3f multiplyMatrix3fByVector3f(const Matrix3f *m, const Vector3f *v);

// Get a row of the matrix as a Vector3f
Vector3f getMatrix3fRow(const Matrix3f *m, int i);

// Get a column of the matrix as a Vector3f
Vector3f getMatrix3fColumn(const Matrix3f *m, int i);

// Rotate matrix around X-axis
Matrix3f rotateX(float angle);

// Rotate matrix around Y-axis
Matrix3f rotateY(float angle);

// Rotate matrix around Z-axis
Matrix3f rotateZ(float angle);

// Print the matrix
void printMatrix3f(const Matrix3f *m);

// Input the matrix
void inputMatrix3f(Matrix3f *m);

#endif // MATRIX3F_H
