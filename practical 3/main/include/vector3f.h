#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <stdio.h>
#include <math.h>

#include "./include/debug.h"

typedef struct {
    float x, y, z;
} Vector3f;

// Initialize a zero vector
void initVector3fZero(Vector3f *v);

// Initialize a unit vector
void initUnitVector3f(Vector3f *v);

// Initialize a vector with given values
void initVector3f(Vector3f *v, float x, float y, float z);

// Check if two vectors are equal
int equals(const Vector3f *lhs, const Vector3f *rhs);

// Calculate the length of the vector
float length(const Vector3f *v);

// Calculate the squared length of the vector
float lengthSquared(const Vector3f *v);

// Normalize the vector
void normalize(Vector3f *v);

// Print the vector
void printVector3f(const Vector3f *v);

// Input the vector
void inputVector3f(Vector3f *v);

#endif // VECTOR3F_H