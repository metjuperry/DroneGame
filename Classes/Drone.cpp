#include "Drone.h"

Drone::Drone()
{
    droneShape.setRadius(24);
    droneShape.setFillColor(sf::Color::Black);
}


void Drone::show(sf::RenderWindow &window) {
    window.draw(droneShape);
}

void Drone::setPosition(float x, float y){
    droneShape.setPosition(x,y);
}


void Drone::restrict(std::pair<int, int> x_borders,std::pair<int, int> y_borders){
    if (x < x_borders.first)
        x = x_borders.first;
    if (x > x_borders.second)
        x = x_borders.second;
    if (y < y_borders.first)
        y = y_borders.first;
    if (y > y_borders.second)
        y = y_borders.second;
}
