#ifndef GAME_H
#define GAME_H

#include "stdafx.h"
#include "Drone.h"
#include "Commands.h"
#include "TimeLine.h"

enum GameStates
{
    UNINITIALISED,
    SETUP,
    PLANNING,
    EXECUTION,
    ENDING
};

class Game
{
public:
    static void StartGame();

private:
    static bool isExiting();
    static void GameLoop();

    static GameStates GameState;
    static sf::RenderWindow mainWindow;

    static void DrawBricks();

    static Drone drone1;
    static void UpdateDrone(Drone *droneToUpdate);

    static std::vector<sf::RectangleShape> Grid;
    static std::vector<Function*> AvailibleCommands;
    static TimeLine executeLine;
    static int Bricks[49];

    static sf::Texture oneBrick;
    static sf::Texture twoBrick;
    static sf::Texture threeBrick;
    static sf::Texture fourBrick;
    static sf::Texture fiveBrick;
};

#endif // GAME_H
