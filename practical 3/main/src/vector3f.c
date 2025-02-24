#include <stdio.h>
#include <math.h>

#include "./include/vector3f.h"

// Initialize a zero vector
void initVector3fZero(Vector3f *v) {
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
}

// Initialize a unit vector
void initUnitVector3f(Vector3f *v) {
    v->x = 1.0f;
    v->y = 1.0f;
    v->z = 1.0f;
}

// Initialize a vector with given values
void initVector3f(Vector3f *v, float x, float y, float z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

// Check if two vectors are equal
int equals(const Vector3f *lhs, const Vector3f *rhs) {
    return (lhs->x == rhs->x && lhs->y == rhs->y && lhs->z == rhs->z);
}

// Calculate the length of the vector
float length(const Vector3f *v) {
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

// Calculate the squared length of the vector
float lengthSquared(const Vector3f *v) {
    return (v->x * v->x + v->y * v->y + v->z * v->z);
}

// Normalize the vector
void normalize(Vector3f *v) {
    float magnitude = length(v);
    if (magnitude > 0) {
        v->x /= magnitude;
        v->y /= magnitude;
        v->z /= magnitude;
    }
}

// Print the vector
void printVector3f(const Vector3f *v) {
    (void)(v);
    DEBUG_MSG("...[ Vector ]...\n");
    DEBUG_MSG("x: %.7f\t y: %.7f\t z: %.7f\n", v->x, v->y, v->z);
}

// Input the vector
void inputVector3f(Vector3f *v) {
    printf("Enter x: ");
    scanf("%f", &v->x);
    printf("Enter y: ");
    scanf("%f", &v->y);
    printf("Enter z: ");
    scanf("%f", &v->z);
}
