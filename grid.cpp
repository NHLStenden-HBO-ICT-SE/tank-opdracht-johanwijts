#include "precomp.h"
#include "grid.h"

namespace Tmpl8
{
	Grid::Grid(int width, int height, int cellSize) :
		m_width(width),
		m_height(height),
		m_cellSize(cellSize) {
		m_numXCells = (int)ceil((float)m_width / m_cellSize);
		m_numYCells = (int)ceil((float)m_height / m_cellSize);

		// Allocate all the cells
		const int TANKS_TO_RESERVE = 20;
		m_cells.resize(m_numYCells * m_numXCells);
		for (size_t i = 0; i < m_cells.size(); i++) {
			m_cells[i].tanks.reserve(TANKS_TO_RESERVE);
		}
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
		int cellX = (int)pos.x / m_cellSize;
		int cellY = (int)pos.y / m_cellSize;

		return getCell(cellX, cellY);
	}

	void Grid::removeTankFromCell(Tank* tank)
	{
		std::vector<Tank*>& tanks = tank->ownerCell->tanks;
		// Normal vector swap
		tanks[tank->cellVectorIndex] = tanks.back();
		tanks.pop_back();
		// Update vector index
		if ((size_t)tank->cellVectorIndex < tanks.size()) {
			tanks[tank->cellVectorIndex]->cellVectorIndex = tank->cellVectorIndex;
		}
		// Set the index of ball to -1
		tank->cellVectorIndex = -1;
		tank->ownerCell = nullptr;
	}
}