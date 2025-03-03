#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h>
#include <stdio.h>

#include "./include/debug.h"

#include "./include/vector3f.h"

// Structure to represent a Quaternion
typedef struct {
    float w, x, y, z;
} Quaternion;

// Initialize a quaternion to default values (0, 0, 0, 0)
void initQuaternion(Quaternion* q);

// Initialize a quaternion with specific values
void initQuaternionValues(Quaternion* q, float w, float x, float y, float z);

// Quaternion multiplication (q1 * q2)
Quaternion multiplyQuaternion(const Quaternion* q1, const Quaternion* q2);

// Compute the conjugate of a quaternion
Quaternion conjugateQuaternion(const Quaternion* q);

// Normalize a quaternion
Quaternion normalizeQuaternion(const Quaternion* q);

// Rotate a vector using a quaternion (angle is in degrees)
Vector3f rotateVector3fByQuaternion(const Quaternion* q, const Vector3f* v, float angle);

// Print the quaternion (output to console)
void printQuaternion(const Quaternion* q);

// Read quaternion values from user input
void inputQuaternion(Quaternion* q);

#endif // QUATERNION_H
