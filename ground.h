//
// Created by Nur Eser on 12.03.2023.
//

#ifndef CMPE460_HW1_GROUND_H
#define CMPE460_HW1_GROUND_H
#include "vector3.h"
#include "ray.h"
#include <algorithm>
class ground
{
public:
    vector3 center;
    vector3 normal;
    vector3 corner1;
    vector3 corner2;
    vector3 color;
    float k_a;
    float k_s;
    float k_d;
    bool is_reflective;

    ground(vector3 center,vector3 normal, vector3 width, vector3 color ,float k_a,float k_d,float k_s,bool is_reflective)
    {
        this->center = center;
        this-> normal = normal.Normalize();
        vector3 height = cross(normal, width);
        corner1 = center + width*0.5 + height*0.5 + normal*0.01;
        corner2 = center - width*0.5 - height*0.5 - normal*0.01;
        this->color = color;
        this->k_a = k_a;
        this->k_d = k_d;
        this->k_s = k_s;
        this-> is_reflective = is_reflective;
    }

    bool RayPlaneIntersection(ray incoming_ray, vector3& intersection_point)
    {
        float num = dot(center-incoming_ray.point,normal);
        float denum = dot(incoming_ray.direction.Normalize(),normal);
        float t = num/denum;
        if(t<0 )
        {
            return false;
        }
        intersection_point = incoming_ray.point + incoming_ray.direction.Normalize()*t;
        bool IsIn = false;
        float minX = std::min(corner1[0],corner2[0]);
        float minY = std::min(corner1[1],corner2[1]);
        float minZ = std::min(corner1[2],corner2[2]);
        float maxX = std::max(corner1[0],corner2[0]);
        float maxY = std::max(corner1[1],corner2[1]);
        float maxZ = std::max(corner1[2],corner2[2]);

        if(intersection_point[0]<=maxX && intersection_point[0]>=minX
        && intersection_point[1]<=maxY && intersection_point[1]>=minY
        &&intersection_point[2]<=maxZ &&intersection_point[2]>=minZ)
        {
            IsIn = true;
        }
        return IsIn;
    }
};



#endif //CMPE460_HW1_GROUND_H
