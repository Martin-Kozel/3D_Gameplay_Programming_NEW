#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <math.h>

#include <stdio.h>

#include "./include/quaternion.h"

// Function to initialize a quaternion to default values (0, 0, 0, 0)
void initQuaternion(Quaternion *q)
{
    q->w = 0.0f;
    q->x = 0.0f;
    q->y = 0.0f;
    q->z = 0.0f;
}

// Function to initialize a quaternion with specific values
void initQuaternionValues(Quaternion *q, float w, float x, float y, float z)
{
    q->w = w;
    q->x = x;
    q->y = y;
    q->z = z;
}

// Quaternion multiplication operator (q1 * q2)
Quaternion multiplyQuaternion(const Quaternion *q1, const Quaternion *q2)
{
    Quaternion result;
    result.w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
    result.x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
    result.y = q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q1->x * q2->z;
    result.z = q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x;
    return result;
}

// Function to compute the conjugate of a quaternion
Quaternion conjugateQuaternion(const Quaternion *q)
{
    Quaternion result;
    result.w = q->w;
    result.x = -q->x;
    result.y = -q->y;
    result.z = -q->z;
    return result;
}

// Function to normalize a quaternion
Quaternion normalizeQuaternion(const Quaternion *q)
{
    float magnitude = q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z;
    if (magnitude > 0.001f)
    {
        magnitude = sqrt(magnitude);
        Quaternion result = {
            q->w / magnitude,
            q->x / magnitude,
            q->y / magnitude,
            q->z / magnitude};
        return result;
    }
    else
    {
        Quaternion result = {1.0f, 0.0f, 0.0f, 0.0f};
        return result;
    }
}

// Function to rotate a vector using a quaternion
// Assumes Vector3f structure exists
Vector3f rotateVector3fByQuaternion(const Quaternion *q, const Vector3f *v, float angle)
{
    Vector3f rotated;

    if (!q || !v) {
        // return Zero Vector is there is an error
        initVector3fZero(&rotated);
        return rotated;
    }

    // Create rotation axis by normalizing input quaternion
    Quaternion axis = normalizeQuaternion(q);

    float radians = angle * (float)(M_PI / 180.0f);

    // Calculate rotation quaternion
    Quaternion rotation = {
        cosf(radians / 2.0f),
        sinf(radians / 2.0f) * axis.x,
        sinf(radians / 2.0f) * axis.y,
        sinf(radians / 2.0f) * axis.z};

    // Convert vector to pure quaternion representation
    Quaternion vectorAsQuaternion = {0.0f, v->x, v->y, v->z};

    // Perform rotation: result = rotate * vectorAsQuaternion * conjugate
    Quaternion conjugate = conjugateQuaternion(&rotation);
    Quaternion result = multiplyQuaternion(&rotation, &vectorAsQuaternion);
    result = multiplyQuaternion(&result, &conjugate);

    // Convert back to vector
    initVector3f(&rotated, result.x, result.y, result.z);
    return rotated;
}

// Function to print the quaternion
void printQuaternion(const Quaternion *q)
{
    printf("... [Quaternion] ...\n");
    printf("w: %.7f\t", q->w);
    printf("x: %.7f\t", q->x);
    printf("y: %.7f\t", q->y);
    printf("z: %.7f\n", q->z);
}

// Function to read quaternion values from user input
void inputQuaternion(Quaternion *q)
{
    printf("Enter w: ");
    scanf("%f", &q->w);
    printf("Enter x: ");
    scanf("%f", &q->x);
    printf("Enter y: ");
    scanf("%f", &q->y);
    printf("Enter z: ");
    scanf("%f", &q->z);
}
