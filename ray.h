//
// Created by Nur Eser on 12.03.2023.
//

#ifndef CMPE460_HW1_RAY_H
#define CMPE460_HW1_RAY_H
#include "vector3.h"
#include <iostream>

class ray
{
public:
    vector3 point;
    vector3 direction;
    ray(vector3 ray_point,vector3 ray_direction)
    {
        point = ray_point;
        direction = ray_direction;
    }
};
#endif //CMPE460_HW1_RAY_H
