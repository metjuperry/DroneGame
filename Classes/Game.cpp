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

void Game::DrawBricks()
{
    std::string texturePath;
    sf::Texture brickTexture;
    for (int i = 0; i != Grid.size(); i++)
    {
        switch(Bricks[i])
        {
        case 1:
            Grid[i].setTexture(&oneBrick);
            break;
        case 2:
            Grid[i].setTexture(&twoBrick);
            break;
        case 3:
            Grid[i].setTexture(&threeBrick);
            break;
        case 4:
            Grid[i].setTexture(&fourBrick);
            break;
        case 5:
            Grid[i].setTexture(&fiveBrick);
            break;
        default:
            Grid[i].setTexture(nullptr);
        }
    }
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

        drone1.getGridArray(Bricks);

        drone1.x = 1;
        drone1.y = 1;

        oneBrick.loadFromFile("1.png");
        twoBrick.loadFromFile("2.png");
        threeBrick.loadFromFile("3.png");
        fourBrick.loadFromFile("4.png");
        fiveBrick.loadFromFile("5.png");

        executeLine.setPosAndSize(sf::Vector2f(50,450),sf::Vector2f(700,120));

        Move_Right* CommandRight = new Move_Right(&drone1, "arrowRight.png");
        Move_Left* CommandLeft = new Move_Left(&drone1, "arrowLeft.png");
        Move_Up* CommandUp = new Move_Up(&drone1, "arrowUp.png");
        Move_Down* CommandDown = new Move_Down(&drone1, "arrowDown.png");

        Pick_Up* CommandPick = new Pick_Up(&drone1, "pickUp.png");
        Put_Down* CommandPut = new Put_Down(&drone1, "letGo.png");

        CommandRight->setPosition(sf::Vector2f(460,50));
        CommandLeft->setPosition(sf::Vector2f(600, 50));

        CommandUp->setPosition(sf::Vector2f(460, 190));
        CommandDown->setPosition(sf::Vector2f(600, 190));

        CommandPick->setPosition(sf::Vector2f(460, 330));
        CommandPut->setPosition(sf::Vector2f(600, 330));

        AvailibleCommands.push_back(CommandRight);
        AvailibleCommands.push_back(CommandLeft);
        AvailibleCommands.push_back(CommandUp);
        AvailibleCommands.push_back(CommandDown);

        AvailibleCommands.push_back(CommandPick);
        AvailibleCommands.push_back(CommandPut);

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
            DrawBricks();
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
        sf::Event ExecutingEvent;
        while (mainWindow.pollEvent(ExecutingEvent))
        {
            if(ExecutingEvent.type == sf::Event::Closed)
            {
                GameState = ENDING;
                break;
            }
        }

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
            DrawBricks();
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
int Game::Bricks[49] = {0};
sf::Texture Game::oneBrick;
sf::Texture Game::twoBrick;
sf::Texture Game::threeBrick;
sf::Texture Game::fourBrick;
sf::Texture Game::fiveBrick;
