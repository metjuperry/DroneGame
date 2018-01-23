#ifndef PICK_UP_H
#define PICK_UP_H

#include <Function.h>


class Pick_Up : public Function
{
    public:
        using Function::Function;
        void Execute();
};

#endif // PICK_UP_H
