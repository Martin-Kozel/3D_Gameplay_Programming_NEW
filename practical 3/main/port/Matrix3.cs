using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace cube
{
    class Matrix3
    {// The class has nine variables, 3 rows and 3 columns
        public double A11;
        public double A12;
        public double A13;
        public double A21;
        public double A22;
        public double A23;
        public double A31;
        public double A32;
        public double A33;

        // Constructor 1 create a zero matrix
        public Matrix3()
        {
            this.A11 = 0.0;
            this.A12 = 0.0;
            this.A13 = 0.0;
            this.A21 = 0.0;
            this.A22 = 0.0;
            this.A23 = 0.0;
            this.A31 = 0.0;
            this.A32 = 0.0;
            this.A33 = 0.0;
        }

        // Constructor 2
        public Matrix3(Vector3 Row1, Vector3 Row2, Vector3 Row3)
        {  // To allow 3 rows of vectors to be declared as a matrix
            this.A11 = Row1.X;
            this.A12 = Row1.Y;
            this.A13 = Row1.Z;
            this.A21 = Row2.X;
            this.A22 = Row2.Y;
            this.A23 = Row2.Z;
            this.A31 = Row3.X;
            this.A32 = Row3.Y;
            this.A33 = Row3.Z;
        }
        // Constructor 3
        public Matrix3(  double _A11,double _A12,double _A13,
            double _A21, double _A22, double _A23,
            double _A31, double _A32,double _A33)
        {// to allow nine double values
            A11 = _A11;
            A12 = _A12;
            A13 = _A13;
            A21 = _A21;
            A22 = _A22;
            A23 = _A23;
            A31 = _A31;
            A32 = _A32;
            A33 = _A33;
        }

        public static Vector3 operator *(Matrix3 M1, Vector3 V1)
        {// An overloaded operator * to return the  product of the matrix by a vector
            return new Vector3(M1.A11 * V1.X + M1.A12 * V1.Y + M1.A13 * V1.Z,
                                M1.A21 * V1.X + M1.A22 * V1.Y + M1.A23 * V1.Z,
                                M1.A31 * V1.X + M1.A32 * V1.Y + M1.A33 * V1.Z);
        }

        public static Vector3 operator *(Vector3 V1, Matrix3 M1 )
        {// An overloaded operator * to return the  product of the matrix by a vector
            return new Vector3(M1.A11 * V1.X + M1.A21 * V1.Y + M1.A31 * V1.Z,
                                M1.A12 * V1.X + M1.A22 * V1.Y + M1.A32 * V1.Z,
                                M1.A13 * V1.X + M1.A23 * V1.Y + M1.A33 * V1.Z);
        }

        public static Matrix3 Transpose(Matrix3 M1)
        {// a method to transpose a given matrix
            return new Matrix3(M1.A11, M1.A21, M1.A31,
                M1.A12, M1.A22, M1.A32,
                M1.A13, M1.A23, M1.A33);
        }
        public static Matrix3 operator +(Matrix3 M1, Matrix3 M2)
        {// An overloaded operator + to return the  sum of two matrix 
            return new Matrix3(M1.A11 + M2.A11, M1.A12 + M2.A12, M1.A13 + M2.A13,
                M1.A21 + M2.A21, M1.A22 + M2.A22, M1.A23 + M2.A23,
                M1.A31 + M2.A31, M1.A32 + M2.A32, M1.A33 + M2.A33);
        }
        public static Matrix3 operator -(Matrix3 M1, Matrix3 M2)
        {// An overloaded operator * to return the  difference of two matrix
            return new Matrix3(M1.A11 - M2.A11, M1.A12 - M2.A12, M1.A13 - M2.A13,
                M1.A21 - M2.A21, M1.A22 - M2.A22, M1.A23 - M2.A23,
                M1.A31 - M2.A31, M1.A32 - M2.A32, M1.A33 - M2.A33);
        }

        public static Matrix3 operator *(double x, Matrix3 M1)
        {// An overloaded operator * to return the  product of the matrix by a scalar
            Matrix3 answer = new Matrix3();
            answer.A11 = M1.A11 * x ;
            answer.A12 = M1.A12 * x;
            answer.A13 = M1.A13 * x;

            answer.A21 = M1.A21 * x;
            answer.A22 = M1.A22 * x;
            answer.A23 = M1.A23 * x;

            answer.A31 = M1.A31 * x;
            answer.A32 = M1.A32 * x;
            answer.A33 = M1.A33 * x; ;
            
            return answer;
        }

        public static Matrix3 operator *(Matrix3 M1, Matrix3 M2)
        {// An overloaded operator * to return the  product of two matrix
            Matrix3 answer = new Matrix3();
            answer.A11 = M1.Row(0) * M2.Column(0);
            answer.A12 = M1.Row(0) * M2.Column(1);
            answer.A13 = M1.Row(0) * M2.Column(2);

            answer.A21 = M1.Row(1) * M2.Column(0);
            answer.A22 = M1.Row(1) * M2.Column(1);
            answer.A23 = M1.Row(1) * M2.Column(2);

            answer.A31 = M1.Row(2) * M2.Column(0);
            answer.A32 = M1.Row(2) * M2.Column(1);
            answer.A33 = M1.Row(2) * M2.Column(2);


            return answer;
        }


        public static double Determinant(Matrix3 M1)
        {// method to return the determinant of a 3x3 matrix
            //                     aei      -     ahf                  + dhc                     - gec                      +    gbh                    -     dbi   
            return M1.A11 * M1.A22 * M1.A33 - M1.A11 * M1.A32 * M1.A23 + M1.A21 * M1.A32 * M1.A13 - M1.A31 * M1.A22 * M1.A13 + M1.A31 * M1.A12 * M1.A23 - M1.A21 * M1.A12 * M1.A33;
        }

        public Vector3 Row( int i)
        { 
            // a method to return as Row as vector3 0 == first row, default == last row
            switch (i)
            {
                case 0:
                    return new Vector3(A11, A12, A13);                    
                case 1:
                    return new Vector3(A21, A22, A23);                    
                case 2:
                default:
                    return new Vector3(A31, A32, A33);                    
            }
        }

        public Vector3 Column(int i)
        {// a method to return as column as vector3 0 == first column, default == last column
            switch (i)
            {
                case 0:
                    return new Vector3(A11, A21, A31);                    
                case 1:
                    return new Vector3(A12, A22, A32);                    
                case 2:
                default:
                    return new Vector3(A13, A23, A33);                    
            }
        }


        public static Matrix3 Inverse(Matrix3 M1)
        {
            // method to return the inverse of a matrix if exists else zero vector
            double det = Determinant(M1);
            if (det == 0)
                return new Matrix3();
            else
            {
                double scale = 1 / det;
                Matrix3 answer = new Matrix3();
                answer.A11 = scale * (M1.A22 * M1.A33 - M1.A23 * M1.A32); // ei-fh
                answer.A12 = scale * (M1.A13 * M1.A32 - M1.A12 * M1.A33); // ch-bi
                answer.A13 = scale * (M1.A12 * M1.A23 - M1.A13 * M1.A22); // ch-bi

                answer.A21 = scale * (M1.A23 * M1.A31 - M1.A21 * M1.A33); // fg-di
                answer.A22 = scale * (M1.A11 * M1.A33 - M1.A13 * M1.A31); // ai-cg
                answer.A23 = scale * (M1.A13 * M1.A21 - M1.A11 * M1.A23); // cd-af


                answer.A31 = scale * (M1.A21 * M1.A32 - M1.A22 * M1.A31); // dh-eg
                answer.A32 = scale * (M1.A12 * M1.A31 - M1.A11 * M1.A32); // bg-ah
                answer.A33 = scale * (M1.A11 * M1.A22 - M1.A12 * M1.A21); // ae-bd

                return answer;
            }

        }

        public static Matrix3 Rotation(int _angle)
        {
            Double radians = Math.PI / 180 * _angle;
            Matrix3 answer = new Matrix3();
            answer.A11 = Math.Cos(radians);
            answer.A12 = Math.Sin(radians);
            answer.A13 = 0;
            answer.A21 = -Math.Sin(radians);
            answer.A22 = Math.Cos(radians);
            answer.A23 = 0;
            answer.A31 = 0;
            answer.A32 = 0;
            answer.A33 = 1;

            return answer;
        }

        
        public static Matrix3 Translate(int dx, int dy)
        {
            Matrix3 answer = new Matrix3();
            answer.A11 = 1;
            answer.A12 = 0;
            answer.A13 = 0;
            answer.A21 = 0;
            answer.A22 = 1;
            answer.A23 = 0;
            answer.A31 = dx;
            answer.A32 = dy;
            answer.A33 = 1;

            return answer;
        }

        public static Matrix3 Scale(int dx, int dy)
        {
            Matrix3 answer = new Matrix3();
            answer.A11 = (double)dx/100;
            answer.A12 = 0;
            answer.A13 = 0;
            answer.A21 = 0;
            answer.A22 = (double)dy/100;
            answer.A23 = 0;
            answer.A31 = 0;
            answer.A32 = 0;
            answer.A33 = 1;

            return answer;
        }

        public static Matrix3 operator -(Matrix3 M1)
        {
            return -1 * M1;
        }

        public static Matrix3 RotationX(int _angle)
        {
            Double radians = Math.PI / 180 * _angle;
            Matrix3 answer = new Matrix3();
            answer.A11 = 1;
            answer.A12 = 0;
            answer.A13 = 0;
            answer.A21 = 0;
            answer.A22 = Math.Cos(radians);
            answer.A23 = -Math.Sin(radians);
            answer.A31 = 0;
            answer.A32 = Math.Sin(radians);
            answer.A33 = Math.Cos(radians);

            return answer;
        }
        public static Matrix3 RotationY(int _angle)
        {
            Double radians = Math.PI / 180 * _angle;
            Matrix3 answer = new Matrix3();
            answer.A11 = Math.Cos(radians);
            answer.A12 = 0;
            answer.A13 = Math.Sin(radians);
            answer.A21 = 0;
            answer.A22 = 1;
            answer.A23 = 0;
            answer.A31 = -Math.Sin(radians);
            answer.A32 = 0;
            answer.A33 = Math.Cos(radians);

            return answer;
        }
        public static Matrix3 RotationZ(int _angle)
        {
            Double radians = Math.PI / 180 * _angle;
            Matrix3 answer = new Matrix3();
            answer.A11 = Math.Cos(radians);
            answer.A12 = -Math.Sin(radians);
            answer.A13 = 0;
            answer.A21 = Math.Sin(radians);
            answer.A22 = Math.Cos(radians);
            answer.A23 = 0;
            answer.A31 = 0;
            answer.A32 = 0;
            answer.A33 = 1;

            return answer;
        }

        public static Matrix3 Scale3D(int dx)
        {
            Matrix3 answer = new Matrix3();
            answer.A11 = (double)dx / 100;
            answer.A12 = 0;
            answer.A13 = 0;
            answer.A21 = 0;
            answer.A22 = (double)dx / 100;
            answer.A23 = 0;
            answer.A31 = 0;
            answer.A32 = 0;
            answer.A33 = (double)dx / 100;

            return answer;
        }
    }
}
