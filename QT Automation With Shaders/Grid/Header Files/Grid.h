// This class is exported from the dll
#pragma once
#ifndef GRID_H
#define GRID_H	
#include <vector>
#include "pch.h"

namespace PixelGrid
{
	class GRID_API Grid
	{
	public:
		Grid(std::vector<float>& vertices, std::vector<float>& colors, int gridSize);
		~Grid();
	private:
		void storeGrid(std::vector<float>& vertices, std::vector<float>& colors, int gridSize);
	};
}
#endif GRID_H