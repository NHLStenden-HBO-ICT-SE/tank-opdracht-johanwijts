#include "precomp.h"
#include "grid.h"

namespace Tmpl8
{
	Grid::Grid(int width, int height, int cellSize) :
		m_width(width),
		m_height(height),
		m_cellSize(cellSize)
	{
		m_numXCells = ceil((float)m_width / cellSize);
		m_numYCells = ceil((float)m_height / cellSize);

		//Allocate all the Cells
		m_cells.resize(m_numYCells * m_numXCells);
	}

	Grid::~Grid() {

	}

	void Grid::addTank(Tank* tank)
	{
		Cell* cell = getCell(tank->position);
		cell->tanks.push_back(tank);
		tank->ownerCell = cell;
		tank->cellVectorIndex = cell->tanks.size() - 1;
	}

	void Grid::addTank(Tank* tank, Cell* cell)
	{
		cell->tanks.push_back(tank);
		tank->ownerCell = cell;
		tank->cellVectorIndex = cell->tanks.size() - 1;
	}

	Cell* Grid::getCell(int x, int y)
	{
		if (x < 0) x = 0;
		if (x >= m_numXCells) x = m_numXCells - 1;
		if (y < 0) y = 0;
		if (y >= m_numYCells) x = m_numYCells - 1;

		return &m_cells[y * m_numXCells + x];
	}

	Cell* Grid::getCell(const vec2& pos)
	{
		int cellX = (int)(pos.x / m_cellSize);
		int cellY = (int)(pos.y / m_cellSize);

		return getCell(cellX, cellY);
	}

	void Grid::removeTankFromCell(Tank* tank)
	{
		std::vector<Tank*>& tanks = tank->ownerCell->tanks;

		if (tank->cellVectorIndex != tanks.size()) {
			tanks[tank->cellVectorIndex] = tanks.back();
		}		
		tanks.pop_back();

		if ((size_t)tank->cellVectorIndex < tanks.size())
		{
			tanks[tank->cellVectorIndex]->cellVectorIndex = tank->cellVectorIndex;
		}

		tank->cellVectorIndex = -1;
		tank->ownerCell = nullptr;
	}
}