#ifndef MOVE_RIGHT_H
#define MOVE_RIGHT_H

#include <Function.h>


class Move_Right : public Function
{
public:
    using Function::Function;
    void Execute();

    sf::Color background = sf::Color::Black;
};

#endif // MOVE_RIGHT_H
