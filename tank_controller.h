#pragma once

class Tank_Controller {
public:
    // Updates collision
    void updateCollision(Grid* grid);
    /// Checks collision between a ball and a vector of balls, starting at a specific index
    void checkCollision(Tank* ball, std::vector<Tank*>& ballsToCheck, int startingIndex);
    /// Checks collision between two balls
    void checkCollision(Tank& b1, Tank& b2);
};