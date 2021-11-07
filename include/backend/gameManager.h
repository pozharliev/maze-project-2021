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
  std::vector<Lobby*> floors;
  int floorCount;
  int currentFloor;
  olc::Sprite* cutsceneSprite;
  olc::Decal* cutscene;
  bool inCutscene;

public:
  GameManager();

  ~GameManager();

private:
  bool OnUserCreate() override;

  bool OnUserUpdate(float fElapsedTime) override;

  void Game(float fElapsedTime);

  void Cutscene(float fElapsedTime);

  void getInput(float elapsedTime);

};