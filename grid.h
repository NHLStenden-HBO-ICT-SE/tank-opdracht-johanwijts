#pragma once

#include "tank.h";

namespace Tmpl8
{	
	struct Cell {
		std::vector<Tank*> tanks;
	};

	class Grid {
	public:
		Grid(int width, int heigh, int cellSize);
		~Grid();

		// Adds a Tank and determines which Cell it belongs to
		void addTank(Tank* tank);
		// Adds a Tank to the specified Cell
		void addTank(Tank* tank, Cell* cell);
		// Gets Cell based on Cell Coordinates
		Cell* getCell(int x, int y);
		// Gets Cell based on position on the screen
		Cell* getCell(const vec2& pos);
		
		void removeTankFromCell(Tank* tank);	


		std::vector<Cell> m_cells;
		int m_cellSize;
		int m_width;
		int m_height;
		int m_numXCells;
		int m_numYCells;
	};
} // namespace Tmpl8
