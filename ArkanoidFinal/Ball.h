#pragma once

#include "Paddle.h"
#include "TIle.h"
#include <vector>

class Ball
{
private: 
  bool m_bPauseTemp;
  int m_nHp;
  float m_fStepballx, m_fStepbally;
  sf::Sprite m_BallSprite;
public:
  Ball(): m_bPauseTemp(false){}
  int GetHp()const { return m_nHp; }
  void SetPauseTemp(bool temppause) { m_bPauseTemp = temppause; }
  bool GetPauseTemp() const { return m_bPauseTemp; }
  void SetPosition(float x, float y) { m_BallSprite.setPosition(x, y); }
  void SetTexture(sf::Texture& text) { m_BallSprite.setTexture(text); }
  void SetHp(int hp) { m_nHp = hp; }
  void SetStepX(float stepx) { m_fStepballx = stepx; }
  void SetStepY(float stepy) { m_fStepbally = stepy; }
  void BoundsCheck(Paddle& paddle);
  float GetStepX() const {return  m_fStepballx; }
  float GetStepY() const { return  m_fStepbally; }
  void UpdateBall(Paddle& paddle, std::vector<Tile>& vecTiles);
  sf::Sprite& GetSprite()  { return m_BallSprite; }
  void RenderBall(sf::RenderTarget* target) { target->draw(m_BallSprite); }
};

