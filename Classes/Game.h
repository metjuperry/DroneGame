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

struct MouseInfo {
    bool pressed;

    enum CommandType {
        None,
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight
    };

    CommandType Held;
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

    static Drone drone1;
    static void UpdateDrone(Drone *droneToUpdate);

    static std::vector<sf::RectangleShape> Grid;
    static std::vector<Function*> AvailibleCommands;
    static TimeLine executeLine;
    static MouseInfo Mouse;
};

#endif // GAME_H
