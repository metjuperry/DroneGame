#ifndef FUNCTION_H
#define FUNCTION_H

#include "stdafx.h"
#include "Drone.h"

class Function
{
    public:
        Function(Drone * drone, const std::string &filename);
        virtual ~Function();
        virtual void Execute();

        virtual void show(sf::RenderWindow &window);
        void setPosition(sf::Vector2f pos);

        virtual bool collision(sf::Vector2i mouseCoords);

        Drone * droneToControl;
        sf::Sprite sprite;
        sf::RectangleShape renderBox;
        sf::Color background = sf::Color::Red;
        sf::Texture texture;
};

#endif // FUNCTION_H
