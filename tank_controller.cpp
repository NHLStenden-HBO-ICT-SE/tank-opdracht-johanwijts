#include "tank_controller.h"
#include "grid.h"
#include "precomp.h"

void Tank_Controller::updateCollision(Grid* grid) {
    for (size_t i = 0; i < grid->m_cells.size(); i++) {

        int x = i % grid->m_numXCells;
        int y = i / grid->m_numXCells;

        Cell& cell = grid->m_cells[i];

        // Loop through all tanks in a cell
        for (size_t j = 0; j < cell.tanks.size(); j++) {
            Tank* tank = cell.tanks[j];
            // Update with the residing cell
            checkCollision(tank, cell.tanks, j + 1);

            // Update collision with neighbor cells
            if (x > 0) {
                // Left
                checkCollision(tank, grid->getCell(x - 1, y)->tanks, 0);
                if (y > 0) {
                    // Top left
                    checkCollision(tank, grid->getCell(x - 1, y - 1)->tanks, 0);
                }
                if (y < grid->m_numYCells - 1) {
                    // Bottom left
                    checkCollision(tank, grid->getCell(x - 1, y + 1)->tanks, 0);
                }
            }
            // Up cell
            if (y > 0) {
                checkCollision(tank, grid->getCell(x, y - 1)->tanks, 0);
            }
        }
    }
}

void Tank_Controller::checkCollision(Tank* tank, std::vector<Tank*>& tanksToCheck, int startingIndex) {
    for (size_t i = startingIndex; i < tanksToCheck.size(); i++) {
        checkCollision(*tank, *tanksToCheck[i]);
    }
}

void Tank_Controller::checkCollision(Tank& b1, Tank& b2) {
    vec2 dir = b1.get_position() - b2.get_position();
    float dir_squared_len = dir.sqr_length();

    float col_squared_len = (b1.get_collision_radius() + b2.get_collision_radius());
    col_squared_len *= col_squared_len;

    if (dir_squared_len < col_squared_len)
    {
        b1.push(dir.normalized(), 1.f);
    }
}


