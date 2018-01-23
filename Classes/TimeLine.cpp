#include "TimeLine.h"

TimeLine::TimeLine()
{
    ChosenBox.setSize(sf::Vector2f(45.0f, 45.0f));
    ChosenBox.setFillColor(sf::Color::Transparent);
}

void TimeLine::setUpTray()
{
    float sizeOfBox = 45.f;
    for (int i = 0; i != 15; i++)
    {
        sf::RectangleShape action;
        sf::Texture arrow;

        action.setPosition((RenderBox.getPosition().x + (sizeOfBox * i+1)), RenderBox.getPosition().y + sizeOfBox/2);
        action.setOutlineThickness(1);
        action.setSize(sf::Vector2f(sizeOfBox,sizeOfBox));
        action.setFillColor(sf::Color::Cyan);

        ActionTray.emplace_back(action);
    }
}

void TimeLine::setPosAndSize(sf::Vector2f pos,sf::Vector2f dim)
{
    RenderBox.setPosition(pos);
    RenderBox.setSize(dim);
    RenderBox.setFillColor(sf::Color::Cyan);

    setUpTray();
}

bool TimeLine::coliding(sf::Vector2i mouseCoords)
{
    sf::IntRect collisionArea(static_cast<sf::Vector2i>(RenderBox.getPosition()), static_cast<sf::Vector2i>(RenderBox.getSize()));

    return collisionArea.contains(mouseCoords);
}

void TimeLine::show(sf::RenderWindow &window)
{
    window.draw(RenderBox);
    window.draw(ChosenBox);
    for (auto action: ActionTray)
    {
        window.draw(action);
    }
}

void TimeLine::addToList(Function *nextCommand)
{
    FunctionsInTimeline.push_back(nextCommand);

    ActionTray[texture_set_index].setTexture(&nextCommand->texture);
    texture_set_index++;
}

void TimeLine::clearList()
{
    FunctionsInTimeline.clear();
    ActionTray.clear();
    setUpTray();

    texture_set_index = 0;
}

void TimeLine::prepareForExecution(){
    FunctionInQueue = FunctionsInTimeline;
    ChosenBox.setFillColor(sf::Color::Red);
}

void TimeLine::executeList()
{
    ChosenBox.setPosition(ActionTray[use_index].getPosition());

    FunctionInQueue[0]->Execute();
    FunctionInQueue.erase(FunctionInQueue.begin());

    use_index++;
}

void TimeLine::clean_up() {
    ChosenBox.setFillColor(sf::Color::Transparent);
    use_index = 0;
}

int TimeLine::getListLen()
{
    return FunctionsInTimeline.size();
}

int TimeLine::getQueueLen()
{
    return FunctionInQueue.size();
}
