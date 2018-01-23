#ifndef TIMELINE_H
#define TIMELINE_H

#include "stdafx.h"
#include "Commands.h"

class TimeLine
{
    public:
        TimeLine();

        void setPosAndSize(sf::Vector2f pos,sf::Vector2f dim);
        bool coliding(sf::Vector2i mouseCoords);
        void show(sf::RenderWindow &window);
        int getListLen();
        int getQueueLen();
        void clean_up();

        void prepareForExecution();

        void setUpTray();

        void addToList(Function *nextCommand);
        void clearList();
        void executeList();
    private:
        int texture_set_index = 0;
        int use_index = 0;
        sf::RectangleShape RenderBox;
        sf::RectangleShape ChosenBox;

        std::vector<Function*> FunctionInQueue;
        std::vector<Function*> FunctionsInTimeline;
        std::vector<sf::RectangleShape> ActionTray;
};

#endif // TIMELINE_H
