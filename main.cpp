#include <iostream>
#include "bitmap_image.hpp"
#include "sphere.h"
#include "camera.h"
#include "light.h"
#include "ground.h"
#include <algorithm>

float I_a;
int p;

vector3 colorize(ray ray_for_pixel,int rec_depth,std::vector<sphere> sphere_list, ground g,light l,int max_depth)

{
    vector3 color;
    color = vector3(0,0,0);
    char show_ground ='y';
    vector3 point;
    vector3 normal;
    float k_a,k_s,k_d;
    bool any_intersection =false;
    bool is_reflective =false;
    for(int i= 0; i<sphere_list.size(); i++)
    {
        vector3 my_point;
        vector3 my_normal;
        bool does_intersect= sphere_list[i].GetIntersection(ray_for_pixel,my_point,my_normal);
        if(does_intersect )
        {
            if(!any_intersection)
            {
                any_intersection =true;
                point =my_point;
                normal = my_normal;
                color = sphere_list[i].color;
                k_a = sphere_list[i].k_a;
                k_d = sphere_list[i].k_d;
                k_s = sphere_list[i].k_s;
                is_reflective = sphere_list[i].is_reflective;
            }
            else
            {
                float dist1 = distance(point,ray_for_pixel.point);
                float dist2 = distance(my_point,ray_for_pixel.point);
                if(dist2<dist1)
                {

                    point = my_point;
                    normal = my_normal;
                    color = sphere_list[i].color;
                    k_a = sphere_list[i].k_a;
                    k_d = sphere_list[i].k_d;
                    k_s = sphere_list[i].k_s;
                    is_reflective = sphere_list[i].is_reflective;

                }
            }
        }

    }
    if(show_ground == 'y')
    {
        vector3 plane_point;
        bool IsPlaneIntersected = g.RayPlaneIntersection(ray_for_pixel,plane_point);
        if(IsPlaneIntersected)
        {
            if(any_intersection)
            {
                float dist3 = distance(plane_point,ray_for_pixel.point);
                float dist4 = distance(point,ray_for_pixel.point);
                if(dist3<dist4)
                {
                    point = plane_point;
                    color = g.color;
                    normal = g.normal;
                    k_a = g.k_a;
                    k_d = g.k_d;
                    k_s = g.k_s;
                    is_reflective = g.is_reflective;

                }
            }
            else
            {
                point = plane_point;
                color = g.color;
                normal = g.normal;
                k_a = g.k_a;
                k_d = g.k_d;
                k_s = g.k_s;
                is_reflective = g.is_reflective;
                any_intersection = true;

            }
        }
    }

    if(any_intersection)
    {

        float Ls=0,Ld=0;
        ray light_ray =l.GetLightRay(point+normal.Normalize()*0.2f);

        float light_distance = distance(l.light_pos,point);

        Ld += k_d*(l.I/(light_distance*light_distance))*std::max(0.0f,dot(normal.Normalize(),light_ray.direction.Normalize()));
        vector3 v = (point-ray_for_pixel.point).Normalize();
        vector3 h = (v+light_ray.direction).Normalize();
        Ls +=k_s*(l.I/(light_distance*light_distance))*pow(std::max(0.0f,dot(normal,h)),p);
        vector3 random1,random2;
        bool any_obstacle =false;
        for(int i=0 ; i <sphere_list.size(); i++)
        {

            bool intersection =sphere_list[i].GetIntersection(light_ray,random1,random2);
            if(intersection)
            {

                any_obstacle =true;
                break;
            }
        }
        float La = k_a*I_a;
        vector3 specular = vector3(255,255,255)*Ls;
        vector3 ambient = color*La;
        vector3 diffuse= color*Ld;
        vector3 final_color = specular+ambient+diffuse;

        color = final_color;
        if(any_obstacle )
        {
            color = color * 0.3;
        }
        if(rec_depth< max_depth && is_reflective)
        {
            vector3 dir(ray_for_pixel.direction.Normalize()-normal.Normalize()*2*dot(ray_for_pixel.direction.Normalize(),normal.Normalize()));
            ray reflected(point+normal*0.02,dir);
            vector3 next_depth_color = colorize(reflected, rec_depth+1,sphere_list,g,l,10);
            color = color + next_depth_color;
        }

        for(int i=0; i<3 ; i++)
        {
            if(color[i]>255)
            {
                color.coordinates[i] = 255;
            }
        }

        return color;
    }

    }

int main() {
    std::vector<sphere> sphere_list;

    for(int i = 1 ; i <= 2; i++)
    {
        std::cout << "Enter the color of Sphere " << i << ":" << std::endl;
        int R,G,B;
        std::cout << "R (0-255): ";
        std::cin >> R;

        std::cout << "G (0-255): ";
        std::cin >> G;

        std::cout << "B (0-255): ";
        std::cin >> B;

        float Ka, Kd, Ks;
        std::cout << "Enter the material properties for sphere " << i << std::endl;
        std::cout << "Ka: ";
        std::cin >> Ka;
        std::cout << "Ks: ";
        std::cin >> Ks;
        std::cout << "Kd: ";
        std::cin >> Kd;

        if(i == 1)
        {
            sphere_list.emplace_back(
                    sphere(
                            vector3(-90,-90,560),
                            60,
                            vector3(R,G,B),
                            Ka,Ks,Kd,
                            false
                    ));
        }

        else{

            sphere_list.emplace_back(
                    sphere(
                            vector3(80,-120,420),
                            30,
                            vector3(R,G,B),
                            Ka,Ks,Kd,
                            false
                    ));
        }
    }
    std::cout << "Enter the global ambient light intensity (0.3 suggested): ";
    std::cin >> I_a;

    std::cout << "Enter the global specular exponent (10 suggested): ";
    std::cin >> p;

    int I_l;
    std::cout << "Enter the intensity of light (200000 sugggested): ";
    std::cin >> I_l;


    light l(
            vector3(300,300,300),
            I_l);

    ground g(
            vector3(0,-150,550),
            vector3(0,1,0),
            vector3(700,0,0),
            vector3(50,50,50),
            0.8,0.25,0.6,
            true);



    bitmap_image image(1000,1000);
    image.clear();

    camera c(
            vector3(0,0,0),
            vector3(-50,-50,100),
            vector3(50,50,100)
            );

    for(int y=0 ; y<image.height(); y++ )
    {
        for(int x=0; x<image.width(); x++)
        {
            float v = 1.0-float(y)/image.height();
            float u= float(x)/image.width();
            ray ray_for_pixel= c.EyeRayGenerator(u,v);
            vector3 final_color;
            final_color = colorize(ray_for_pixel,0,sphere_list,g,l,15);
            image.set_pixel(x,y,final_color[0],final_color[1],final_color[2]);
        }
    }

    std::cout << "Your image is saved to: image.bmp" << std::endl;
    image.save_image("image.bmp");

    return 0;
}
