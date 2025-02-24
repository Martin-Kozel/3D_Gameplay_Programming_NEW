#include <stdio.h>
#include <math.h>

// define Vector3 structure
typedef struct {
    double x, y, z;
}
Vector3;

// create a zero vector
Vector3 createZeroVector()
{
    Vector3 v = { 0.0, 0.0, 0.0 };
    return v;
}

// Create a vector with specific x, y, z values
Vector3 createVector(double x1, double y1, double z1)
{
    Vector3 v = { x1, y1, z1 };
    return v;
}

// Copy another vector
Vector3 copyVector(Vector3 v)
{
    Vector3 newVector = { v.x, v.y, v.z };
    return newVector;
}

// Calculate the length of the vector
double vectorLength(Vector3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Calculate the squared length of the vector (avoids sqrt)
double vectorLengthSquared(Vector3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

// Normalize the vector (make its length 1)
void normalizeVector(Vector3* v)
{
    double len = vectorLength(*v);
    if (len > 0.0)
    {  // Avoid division by zero
        v->x /= len;
        v->y /= len;
        v->z /= len;
    }
}

// Add two vectors and return the result
Vector3 vectorAdd(Vector3 v1, Vector3 v2)
{
    Vector3 result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return result;
}

// Subtract two vectors and return the result
Vector3 vectorSubtract(Vector3 v1, Vector3 v2)
{
    Vector3 result = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return result;
}

// Negate the vector
Vector3 vectorNegate(Vector3 v)
{
    Vector3 result = { -v.x, -v.y, -v.z };
    return result;
}

// Calculate the dot product of two vectors
double vectorDotProduct(Vector3 v1, Vector3 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// Multiply a vector by a scalar (double)
Vector3 vectorMultiplyScalar(double k, Vector3 v)
{
    Vector3 result = { v.x * k, v.y * k, v.z * k };
    return result;
}

// Multiply a vector by a scalar (float)
Vector3 vectorMultiplyScalarFloat(float k, Vector3 v)
{
    Vector3 result = { v.x * k, v.y * k, v.z * k };
    return result;
}

// Multiply a vector by a scalar (int)
Vector3 vectorMultiplyScalarInt(int k, Vector3 v)
{
    Vector3 result = { v.x * k, v.y * k, v.z * k };
    return result;
}

// Calculate the cross product of two vectors
Vector3 vectorCrossProduct(Vector3 v1, Vector3 v2)
{
    Vector3 result = {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
    return result;
}

// Convert vector to a string (for printing)
void vectorToString(Vector3 v, char* buffer)
{
    snprintf(buffer, 100, "(%.3f, %.3f, %.3f)", v.x, v.y, v.z);
}

int main()
{
    // Create vectors
    Vector3 v1 = createVector(3.0, 4.0, 0.0);
    Vector3 v2 = createVector(1.0, 2.0, 3.0);

    // Test Vector Addition
    Vector3 resultAdd = vectorAdd(v1, v2);
    char buffer[100];
    vectorToString(resultAdd, buffer);
    printf("Vector Addition: %s\n", buffer);

    // Test Vector Subtraction
    Vector3 resultSub = vectorSubtract(v1, v2);
    vectorToString(resultSub, buffer);
    printf("Vector Subtraction: %s\n", buffer);

    // Test Dot Product
    double dotProduct = vectorDotProduct(v1, v2);
    printf("Dot Product: %.3f\n", dotProduct);

    // Test Cross Product
    Vector3 resultCross = vectorCrossProduct(v1, v2);
    vectorToString(resultCross, buffer);
    printf("Cross Product: %s\n", buffer);

    // Test Length
    double length = vectorLength(v1);
    printf("Length of v1: %.3f\n", length);

    // Normalize v1 and print
    normalizeVector(&v1);
    vectorToString(v1, buffer);
    printf("Normalized v1: %s\n", buffer);

    return 0;
}
