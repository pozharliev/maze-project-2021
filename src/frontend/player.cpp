#include "../../include/frontend/player.h"

void Player::innitPlayer()
{
  firstPlayerMove = true;
  playerAnimSpritesheet = new olc::Renderable();
  playerAnimSpritesheet->Load("public/Player_Anim_Spritesheet.png");
  Animator = new olc::AnimatedSprite();
  Animator->mode = olc::AnimatedSprite::SPRITE_MODE::SINGLE;
  Animator->type = olc::AnimatedSprite::SPRITE_TYPE::DECAL;
  Animator->spriteSheet = playerAnimSpritesheet;
  Animator->SetSpriteSize({32, 32});
  Animator->SetSpriteScale(0.75f);

  setUpAnimations();
}

void Player::setUpAnimations()
{
  Animator->AddState("upIdle", 0.07f, olc::AnimatedSprite::PLAY_MODE::LOOP, std::vector<olc::vi2d>{{64, 0}} );

  Animator->AddState("downIdle", 0.07f, olc::AnimatedSprite::PLAY_MODE::LOOP, std::vector<olc::vi2d>{{64, 32}} );

  Animator->AddState("leftIdle", 0.07f, olc::AnimatedSprite::PLAY_MODE::LOOP, std::vector<olc::vi2d>{{64, 64}} );

  Animator->AddState("rightIdle", 0.07f, olc::AnimatedSprite::PLAY_MODE::LOOP, std::vector<olc::vi2d>{{64, 96}} );

  Animator->AddState("up", 0.07f, olc::AnimatedSprite::PLAY_MODE::LOOP, std::vector<olc::vi2d>{
    {0,0},
    {32, 0},
    {64, 0},
    {96, 0},
    {128, 0},
    {160, 0},
    {192, 0},
    {224, 0},
    {256, 0},
    {288, 0},
    {320, 0},
    {352, 0}
  });

  Animator->AddState("down", 0.07f, olc::AnimatedSprite::PLAY_MODE::LOOP, std::vector<olc::vi2d>{
    {0,32},
    {32, 32},
    {64, 32},
    {96, 32},
    {128, 32},
    {160, 32},
    {192, 32},
    {224, 32},
    {256, 32},
    {288, 32},
    {320, 32},
    {352, 32}
  });

  Animator->AddState("left", 0.07f, olc::AnimatedSprite::PLAY_MODE::LOOP, std::vector<olc::vi2d>{
    {0,64},
    {32, 64},
    {64, 64},
    {96, 64},
    {128, 64},
    {160, 64},
    {192, 64},
    {224, 64},
    {256, 64},
    {288, 64},
    {320, 64},
    {352, 64}
  });

  Animator->AddState("right", 0.07f, olc::AnimatedSprite::PLAY_MODE::LOOP, std::vector<olc::vi2d>{
    {0, 96},
    {32, 96},
    {64, 96},
    {96, 96},
    {128, 96},
    {160, 96},
    {192, 96},
    {224, 96},
    {256, 96},
    {288, 96},
    {320, 96},
    {352, 96}
  });

  Animator->SetState("upIdle");

}


void Player::movePlayer(olc::PixelGameEngine* engine, olc::Key dir, float elapsedTime)
  {
    switch(dir)
    {
      case olc::LEFT:
        firstPlayerMove = false;
        playerVelX = -playerSpeed;
        playerX += playerVelX * elapsedTime;
        Animator->SetState("left");
        playerDir = PLAYER_DIRS::LEFT;
        break;

      case olc::RIGHT:
        firstPlayerMove = false;
        playerVelX = playerSpeed;
        playerX += playerVelX * elapsedTime;
        Animator->SetState("right");
        playerDir = PLAYER_DIRS::RIGHT;
        break;

      case olc::UP:
        firstPlayerMove = false;
        playerVelY = -playerSpeed;
        playerY += playerVelY * elapsedTime;
        Animator->SetState("up");
        playerDir = PLAYER_DIRS::UP;
        break;

      case olc::DOWN:
        firstPlayerMove = false;
        playerVelY = playerSpeed;
        playerY += playerVelY * elapsedTime;
        Animator->SetState("down");
        playerDir = PLAYER_DIRS::DOWN;
        break;

      default:
      break;
    }

    newPlayerPosX = playerX + playerVelX * elapsedTime;
    newPlayerPosY = playerY + playerVelY * elapsedTime;

  }

void Player::drawPlayer(olc::PixelGameEngine* engine, float elapsedTime)
  {
    //olc::vf2d playerSize = {25.0f, 25.0f};
    Animator->Draw(elapsedTime, {playerX-11.0f, playerY-22.0f});
  }
