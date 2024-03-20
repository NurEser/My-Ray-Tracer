//
// Created by Nur Eser on 12.03.2023.
//

#ifndef CMPE460_HW1_VECTOR3_H
#define CMPE460_HW1_VECTOR3_H
#include <iostream>
#include "cmath"
class vector3
{
public:
    float coordinates[3];
    vector3()
    {
        coordinates[0] = 0;
        coordinates[1] = 0;
        coordinates[2] = 0;

    }

    vector3(float x,float y ,float z)
    {
        coordinates[0] = x;
        coordinates[1] = y;
        coordinates[2] = z;
    }

    inline float operator[](int index)
    {
        return coordinates[index];
    }
    inline float operator[] (int index) const
    {
        return coordinates[index];
    }

    float GetLength()
    {
        return sqrt((coordinates[0]*coordinates[0])+(coordinates[1]*coordinates[1])+(coordinates[2]*coordinates[2]));
    }

    vector3 Normalize()
    {
        float length = GetLength();
        return vector3(coordinates[0]/length, coordinates[1]/length, coordinates[2]/length);
    }

};



inline std::ostream& operator<<(std::ostream &out, const vector3 &v) {
    return out << "[" <<v.coordinates[0] << ", " << v.coordinates[1] << ", " << v.coordinates[2] << "]";
}

inline vector3 operator+(const vector3& v1, const vector3& v2 )
{
    return vector3(v1[0]+v2[0],v1[1]+v2[1],v1[2]+v2[2]);
}

//inline vector3 operator+=(const vector3& v1, const vector3& v2 )
//{
//    return vector3(v1[0]+v2[0],v1[1]+v2[1],v1[2]+v2[2]);
//}




inline vector3 operator-(const vector3& v1, const vector3& v2 )
{
    return vector3(v1[0]-v2[0],v1[1]-v2[1],v1[2]-v2[2]);
}

inline float distance(const vector3& v1, const vector3& v2)
{
    return (v1-v2).GetLength();
}

inline vector3 operator*(const vector3& v1, float num)
{
    return vector3(v1[0]*num,v1[1]*num,v1[2]*num);
}

inline float dot (const vector3& v1, const vector3& v2 )
{
    return  (v1[0]*v2[0])+(v1[1]*v2[1])+(v1[2]*v2[2]);
}


inline vector3 cross(const vector3& lhs, const vector3 rhs)
{
    return vector3(lhs[1]*rhs[2] - lhs[2]*rhs[1],lhs[2]*rhs[0] - lhs[0]*rhs[2],lhs[0]*rhs[1] - lhs[1]*rhs[0]);
}

#endif //CMPE460_HW1_VECTOR3_H
