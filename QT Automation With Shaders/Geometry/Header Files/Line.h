#pragma once
#ifndef LINE_H
#define LINE_H
#include "Point.h"

namespace GeometricEntity
{
	class GEOMETRY_API Line
	{
	public:
		Line(Point p1, Point p2);
		~Line();

	public:
		Point getP1();
		Point getP2();
		void setP1(Point);
		void setP2(Point);
	private:
		Point mP1;
		Point mP2;
	};
}
#endif LINE_H