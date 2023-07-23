#ifndef MATH_H
#define MATH_H
#include <iostream>

struct Vector2f
{
    Vector2f(float p_x = 0.0, float p_y = 0.0)
    : x(p_x), y(p_y)
    {};

    void print(){
        std::cout << "<" << x << ", " << y << ">" << std::endl;
    }

    float x, y;

};

#endif