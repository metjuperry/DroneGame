#ifndef DRONE_H
#define DRONE_H

#include "stdafx.h"

class Drone
{
public:
    Drone();
    void show(sf::RenderWindow &window);
    void setPosition(float x, float y);

    void restrict(std::pair<int, int> x_borders,std::pair<int, int> y_borders);

    int x;
    int y;

    bool hold;

    sf::CircleShape droneShape;
};

#endif // DRONE_H
