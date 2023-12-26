#include "pch.h"
#include "Point.h"
using namespace GeometricEntity;

Point::Point(float inX, float inY): mX(0), mY(0)
{
    mX = inX;
    mY = inY;
}

Point::~Point()
{
}

float Point::x()
{
    return mX;
}

float Point::y()
{
    return mY;
}



void Point::setX(float x)
{
    mX = x;
}

void Point::setY(float y)
{
    mY = y;
}
