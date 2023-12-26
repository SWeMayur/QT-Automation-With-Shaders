#pragma once
#ifndef POINT_H
#define POINT_H
#include "pch.h"

namespace GeometricEntity {

    class GEOMETRY_API Point
    {
    public:
        Point(float inX, float inY);
        ~Point();

        float x();
        float y();

        void setX(float x);
        void setY(float y);

    private:
        float mX;
        float mY;
    };
}
#endif POINT_H


