//
// Created by Nur Eser on 12.03.2023.
//

#ifndef CMPE460_HW1_LIGHT_H
#define CMPE460_HW1_LIGHT_H
#include "ray.h"

class light
{
public:
    vector3 light_pos;
    float I;
    light(vector3 light_pos, float I)
    {
        this->I =I;
        this->light_pos = light_pos;
    }


    ray GetLightRay(const vector3& point)
    {
        return ray(point, light_pos-point);
    }
};
#endif //CMPE460_HW1_LIGHT_H
