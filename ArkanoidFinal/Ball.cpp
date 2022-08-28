#include "Ball.h"
void Ball::BoundsCheck(Paddle& paddle) {
  if (m_BallSprite.getPosition().x < 0 || m_BallSprite.getPosition().x > 600) {
    m_fStepballx = -m_fStepballx;

  }
  else if (m_BallSprite.getPosition().y < 0) {
    m_fStepbally = -m_fStepbally;
  }
  else if (m_BallSprite.getPosition().y > 600) {
    m_bPauseTemp = true;
    m_nHp--;
    m_BallSprite.setPosition(paddle.GetSprite().getPosition().x + 16, paddle.GetSprite().getPosition().y - 8);

  }
  else if (m_BallSprite.getPosition().x == 0 && m_BallSprite.getPosition().y == 0) {
    m_BallSprite.setPosition(2, 2);
    m_fStepbally = -m_fStepbally;
  }
  else if (m_BallSprite.getPosition().x == 600 && m_BallSprite.getPosition().y == 600) {
    m_BallSprite.setPosition(598, 598);
    m_fStepballx = -m_fStepballx;
  }
  else if (m_BallSprite.getPosition().x == 0 && m_BallSprite.getPosition().y == 600) {
    m_BallSprite.setPosition(2, 598);
    m_fStepballx = -m_fStepballx;
  }
  else if (m_BallSprite.getPosition().x == 600 && m_BallSprite.getPosition().y == 0) {
    m_BallSprite.setPosition(598, 2);
    m_fStepballx = -m_fStepballx;
  }

}
void Ball::UpdateBall(Paddle& paddle, std::vector<Tile>& vecTiles) {
  if (!m_nHp || m_bPauseTemp) { return; }
  BoundsCheck(paddle);
  m_BallSprite.move(m_fStepballx, 0);
  if (m_BallSprite.getGlobalBounds().intersects(paddle.GetSprite().getGlobalBounds())) {
    m_fStepballx = -m_fStepballx;
  }
  else
    for (auto item : vecTiles) {
      if (item.GetSprite().getGlobalBounds().intersects(m_BallSprite.getGlobalBounds()))
      {
        m_fStepballx = -m_fStepballx;
      }
    }
  m_BallSprite.move(0, m_fStepbally);
  if (m_BallSprite.getGlobalBounds().intersects(paddle.GetSprite().getGlobalBounds())) {
    m_fStepbally = -m_fStepbally;
  }
  else
    for (auto item : vecTiles) {
      if (item.GetSprite().getGlobalBounds().intersects(m_BallSprite.getGlobalBounds()))
      {
        m_fStepbally = -m_fStepbally;
      }
    }
}