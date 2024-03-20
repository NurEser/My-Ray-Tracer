//
// Created by Nur Eser on 12.03.2023.
//

#ifndef CMPE460_HW1_CAMERA_H
#define CMPE460_HW1_CAMERA_H
#include "ray.h"
#include "vector3.h"
#include <iostream>

class camera
{
public:
    vector3 eye_origin;
    vector3 plane_bottom_left_corner;
    vector3 plane_width;
    vector3 plane_height;
    camera(vector3 eye_origin,vector3 plane_bottom_left_corner,vector3 plane_upper_right_corner )
    {
        this->eye_origin = eye_origin;
        this->plane_bottom_left_corner = plane_bottom_left_corner;
        plane_width = vector3(plane_upper_right_corner[0]-plane_bottom_left_corner[0],0,0);
        plane_height = vector3(0,plane_upper_right_corner[1]-plane_bottom_left_corner[1],0);
    }

    ray EyeRayGenerator(float u, float v)
    {
        vector3 ray_direction = (plane_bottom_left_corner + plane_width*u + plane_height*v )-eye_origin;
        return ray(eye_origin,ray_direction);
    }
};
#endif //CMPE460_HW1_CAMERA_H
