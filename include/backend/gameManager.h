#pragma once

#include "../../libs/libs.h"
#include "../frontend/mainMenu.h"
#include "../frontend/lobby.h"
#include "../frontend/player.h"
#include "../backend/collisions.h"

class GameManager : public olc::PixelGameEngine
{

public:
    MainMenu *mainMenu;
    Player *player;
    Collisions *collisions;
    std::vector<Lobby *> floors;
    int floorCount;
    int currentFloor;
    olc::Sprite *cutsceneSprite;
    olc::Decal *cutscene;
    bool inCutscene;
    bool vignette;

public:
    GameManager();

    ~GameManager();

private:
    /**
    * @brief This function is called once, at the start of the program, used for setting up general settings and data.
    **/
    bool OnUserCreate() override;

    /**
    * @brief This function is called each frame.
    **/
    bool OnUserUpdate(float fElapsedTime) override;


    /**
    * @brief Contains the core logic for the game.
    **/
    void Game(float fElapsedTime);

    /**
    * @brief Used for managing the custcene.
    **/
    void Cutscene(float fElapsedTime);


    /**
    * @brief Listens for input from the user.
    **/
    void getInput(float elapsedTime);
};