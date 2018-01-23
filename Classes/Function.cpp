#include "Function.h"

Function::Function(Drone * drone, const std::string &filename)
{
    droneToControl = drone;
    texture.loadFromFile(filename);

    renderBox.setPosition(sf::Vector2f(0,0));
    renderBox.setTexture(&texture);
    renderBox.setSize(sf::Vector2f(70,70));

}

Function::~Function()
{
}

void Function::Execute()
{
    std::cout << "Executing" << std::endl;
}

bool Function::collision(sf::Vector2i mouseCoords)
{
    sf::IntRect collisionArea(static_cast<sf::Vector2i>(renderBox.getPosition()), static_cast<sf::Vector2i>(renderBox.getSize()));

    return collisionArea.contains(mouseCoords);
}

void Function::setPosition(sf::Vector2f pos)
{
    renderBox.setPosition(pos);
}

void Function::show(sf::RenderWindow &window)
{
    window.draw(renderBox);
}
