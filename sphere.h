//
// Created by Nur Eser on 12.03.2023.
//

#ifndef CMPE460_HW1_SPHERE_H
#define CMPE460_HW1_SPHERE_H
#include "ray.h"
class sphere
{
public:
    vector3 center;
    float radius;
    vector3 color;
    float k_a;
    float k_s;
    float k_d;
    bool is_reflective;
    sphere(vector3 center, float radius,vector3 color)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
        k_a = 1;
        k_d =0;
        k_s =0;
    }
    sphere(vector3 center, float radius,vector3 color,float k_a , float k_s,float k_d,bool is_reflective)
    {
        this->center = center;
        this->radius = radius;
        this->color = color;
        this->k_a = k_a;
        this->k_d = k_d;
        this->k_s = k_s;
        this-> is_reflective = is_reflective;

    }


    bool GetIntersection(ray incoming_ray, vector3& point, vector3& normal)
    {
        vector3 OC = center-incoming_ray.point;
        if (dot(OC,incoming_ray.direction.Normalize()) < 0)
        {
            return false;
        }
        vector3 projection = incoming_ray.direction.Normalize()*dot(OC,incoming_ray.direction.Normalize());
        float distance = (OC-projection).GetLength();
        if(distance>=radius){return false;}
        float deltat = sqrt(radius*radius-distance*distance);
        vector3 deltavector = projection.Normalize()*deltat;
        point = projection-deltavector + incoming_ray.point;
        normal = (point-center).Normalize();
        return true;
    }
};

#endif //CMPE460_HW1_SPHERE_H
