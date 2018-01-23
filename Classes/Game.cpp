#include "Game.h"

void Game::StartGame()
{
    if (GameState != UNINITIALISED)
        return;

    mainWindow.create(sf::VideoMode(800,600), "Drones!");
    GameState = SETUP;

    while (!isExiting())
    {
        GameLoop();
    }
    mainWindow.close();
}

bool Game::isExiting()
{
    return (GameState == ENDING);
}

void Game::UpdateDrone(Drone *droneToUpdate)
{
    std::pair <int,int> x_size;
    std::pair <int,int> y_size;

    x_size = std::make_pair(0,6);
    y_size = std::make_pair(0,6);

    droneToUpdate->restrict(x_size, y_size);

    droneToUpdate->setPosition(Grid[droneToUpdate->y * 7 + droneToUpdate->x].getPosition().x,Grid[droneToUpdate->y * 7 + droneToUpdate->x].getPosition().y);
}

void Game::GameLoop()
{
    switch(GameState)
    {
    case SETUP:
    {
        sf::Event SetupEvent;
        while (mainWindow.pollEvent(SetupEvent))
        {
            if(SetupEvent.type == sf::Event::Closed)
            {
                GameState = ENDING;
            }
        }

        sf::RectangleShape rectangle;

        double x = 1;
        double y = 1;

        int boxSize = 50;

        for (int rows = 0; rows != 7; rows++)
        {
            for (int cols = 0; cols != 7; cols++)
            {
                rectangle.setSize(sf::Vector2f(boxSize,boxSize));
                rectangle.setOutlineColor(sf::Color::Black);
                rectangle.setOutlineThickness(2);
                rectangle.setPosition(x*boxSize,y*boxSize);

                Grid.emplace_back(rectangle);
                x += 1;
            }
            x = 1;
            y += 1;
        }

        drone1.x = 1;
        drone1.y = 1;

        executeLine.setPosAndSize(sf::Vector2f(50,450),sf::Vector2f(700,120));

        Move_Right* CommandRight = new Move_Right(&drone1, "arrowRight.png");
        Move_Left* CommandLeft = new Move_Left(&drone1, "arrowLeft.png");
        Move_Up* CommandUp = new Move_Up(&drone1, "arrowUp.png");
        Move_Down* CommandDown = new Move_Down(&drone1, "arrowDown.png");

        CommandRight->setPosition(sf::Vector2f(460,50));
        CommandLeft->setPosition(sf::Vector2f(600, 50));

        CommandUp->setPosition(sf::Vector2f(460, 190));
        CommandDown->setPosition(sf::Vector2f(600, 190));

        AvailibleCommands.push_back(CommandRight);
        AvailibleCommands.push_back(CommandLeft);
        AvailibleCommands.push_back(CommandUp);
        AvailibleCommands.push_back(CommandDown);

        Mouse.Held = MouseInfo::None;

        GameState = PLANNING;
        break;
    }

    case PLANNING:
    {
        sf::Event PlanningEvent;
        while (mainWindow.pollEvent(PlanningEvent))
        {
            if (PlanningEvent.type == sf::Event::Closed)
            {
                GameState = ENDING;
                break;
            }
            else if (PlanningEvent.type == sf::Event::KeyPressed)
            {
                if (PlanningEvent.key.code == sf::Keyboard::Space)
                {
                    if (executeLine.getListLen() > 0)
                    {
                        executeLine.prepareForExecution();
                        GameState = EXECUTION;
                    }
                }
            }
            else if (PlanningEvent.type == sf::Event::EventType::MouseButtonPressed &&
                     sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                for (auto command : AvailibleCommands)
                {
                    if (command->collision(sf::Mouse::getPosition(mainWindow)))
                    {
                        if (executeLine.getListLen() != 15)
                            executeLine.addToList(command);
                    }
                }

                if (executeLine.coliding(sf::Mouse::getPosition(mainWindow)))
                {
                    executeLine.clearList();
                }
            }
        }

        UpdateDrone(&drone1);

        mainWindow.clear(sf::Color::White);
        for (auto rectangle : Grid)
        {
            mainWindow.draw(rectangle);
            drone1.show(mainWindow);
            executeLine.show(mainWindow);

            for (auto command:AvailibleCommands)
            {
                command->show(mainWindow);
            }
        }
        mainWindow.display();
        break;
    }
    case EXECUTION:
    {

        if (executeLine.getQueueLen() == 0)
        {
            executeLine.clean_up();
            GameState = PLANNING;
            break;
        }

        executeLine.executeList();

        UpdateDrone(&drone1);

        mainWindow.clear(sf::Color::White);
        for (auto rectangle : Grid)
        {
            mainWindow.draw(rectangle);
            drone1.show(mainWindow);
            executeLine.show(mainWindow);
        }
        mainWindow.display();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    }
}

GameStates Game::GameState = UNINITIALISED;
sf::RenderWindow Game::mainWindow;
std::vector<sf::RectangleShape> Game::Grid;
std::vector<Function*> Game::AvailibleCommands;
Drone Game::drone1;
TimeLine Game::executeLine;
MouseInfo Game::Mouse;
