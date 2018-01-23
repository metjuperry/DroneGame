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
    void getGridArray(int *_BrickArray);

    void pickUp();
    void putDown();

    int x;
    int y;

    bool hold;

    int *BrickArray;
    sf::CircleShape droneShape;
};

#endif // DRONE_H
