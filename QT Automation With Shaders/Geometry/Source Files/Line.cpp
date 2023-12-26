#include "pch.h"
#include "Line.h"
using namespace GeometricEntity;

Line::Line(Point p1, Point p2) : mP1(p1), mP2(p2)
{
}
Line::~Line() {}

Point Line::getP1()
{
	return mP1;
}

Point Line::getP2()
{
	return mP2;
}

void Line::setP1(Point p)
{
	mP1 = p;
}

void Line::setP2(Point p)
{
	mP2 = p;
}