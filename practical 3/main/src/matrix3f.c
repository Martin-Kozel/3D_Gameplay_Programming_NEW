#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <math.h>

#include <stdio.h>

#include "./include/matrix3f.h"


// Initialize a zero matrix
void initMatrix3fZero(Matrix3f *m) {
    m->A11 = 0.0f; m->A12 = 0.0f; m->A13 = 0.0f;
    m->A21 = 0.0f; m->A22 = 0.0f; m->A23 = 0.0f;
    m->A31 = 0.0f; m->A32 = 0.0f; m->A33 = 0.0f;
}

// Initialize a matrix with rows as Vector3f
void initMatrix3fWithRows(Matrix3f *m, const Vector3f *row1, const Vector3f *row2, const Vector3f *row3) {
    m->A11 = row1->x; m->A12 = row1->y; m->A13 = row1->z;
    m->A21 = row2->x; m->A22 = row2->y; m->A23 = row2->z;
    m->A31 = row3->x; m->A32 = row3->y; m->A33 = row3->z;
}

// Initialize a matrix with values
void initMatrix3fWithValues(Matrix3f *m, float A11, float A12, float A13,
                             float A21, float A22, float A23,
                             float A31, float A32, float A33) {
    m->A11 = A11; m->A12 = A12; m->A13 = A13;
    m->A21 = A21; m->A22 = A22; m->A23 = A23;
    m->A31 = A31; m->A32 = A32; m->A33 = A33;
}

// Matrix multiplication with a Vector3f
Vector3f multiplyMatrix3fByVector3f(const Matrix3f *m, const Vector3f *v) {
    return (Vector3f){
        m->A11 * v->x + m->A12 * v->y + m->A13 * v->z,
        m->A21 * v->x + m->A22 * v->y + m->A23 * v->z,
        m->A31 * v->x + m->A32 * v->y + m->A33 * v->z
    };
}

// Get a row of the matrix as a Vector3f
Vector3f getMatrix3fRow(const Matrix3f *m, int i) {
    switch (i) {
        case 0: return (Vector3f){m->A11, m->A12, m->A13};
        case 1: return (Vector3f){m->A21, m->A22, m->A23};
        case 2: return (Vector3f){m->A31, m->A32, m->A33};
        default: return (Vector3f){0.0f, 0.0f, 0.0f};
    }
}

// Get a column of the matrix as a Vector3f
Vector3f getMatrix3fColumn(const Matrix3f *m, int i) {
    switch (i) {
        case 0: return (Vector3f){m->A11, m->A21, m->A31};
        case 1: return (Vector3f){m->A12, m->A22, m->A32};
        case 2: return (Vector3f){m->A13, m->A23, m->A33};
        default: return (Vector3f){0.0f, 0.0f, 0.0f};
    }
}

// Rotate matrix around X-axis
Matrix3f rotateX(float angle) {
    float radians = angle * (M_PI / 180.0f);
    Matrix3f result;
    initMatrix3fWithValues(&result,
        1.0f, 0.0f, 0.0f,
        0.0f, cosf(radians), -sinf(radians),
        0.0f, sinf(radians), cosf(radians)
    );
    return result;
}

// Rotate matrix around Y-axis
Matrix3f rotateY(float angle) {
    float radians = angle * (M_PI / 180.0f);
    Matrix3f result;
    initMatrix3fWithValues(&result,
        cosf(radians), 0.0f, -sinf(radians),
        0.0f, 1.0f, 0.0f,
        sinf(radians), 0.0f, cosf(radians)
    );
    return result;
}

// Rotate matrix around Z-axis
Matrix3f rotateZ(float angle) {
    float radians = angle * (M_PI / 180.0f);
    Matrix3f result;
    initMatrix3fWithValues(&result,
        cosf(radians), -sinf(radians), 0.0f,
        sinf(radians), cosf(radians), 0.0f,
        0.0f, 0.0f, 1.0f
    );
    return result;
}

// Print the matrix
void printMatrix3f(const Matrix3f *m) {
    DEBUG_MSG("...[ Matrix ]...\n");
    for (int i = 0; i < 3; i++) {
        Vector3f row = getMatrix3fRow(m, i);
        (void)(row);
        DEBUG_MSG("(%.2f, %.2f, %.2f)\n", row.x, row.y, row.z);
    }
}

// Input the matrix
void inputMatrix3f(Matrix3f *m) {
    Vector3f rows[3];
    for (int i = 0; i < 3; i++) {
        printf("Enter Matrix Row %d (x y z): ", i);
        scanf("%f %f %f", &rows[i].x, &rows[i].y, &rows[i].z);
    }
    initMatrix3fWithRows(m, &rows[0], &rows[1], &rows[2]);
}