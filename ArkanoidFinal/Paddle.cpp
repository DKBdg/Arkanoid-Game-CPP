#include "Paddle.h"
Paddle:: Paddle(sf::Texture& texture, float Stepx, float xscale ) : m_fScaleX(xscale), m_fStepX(Stepx) {
  m_Paddlesprite.setTexture(texture);
  m_Paddlesprite.setScale(m_fScaleX, 1);
}
void Paddle:: UpdatePaddle(int i) {
  if (i == Directions::Left && m_Paddlesprite.getPosition().x > 0) {
    m_Paddlesprite.move(-m_fStepX, 0);

  }
  else if (i == Directions::Right && m_Paddlesprite.getPosition().x + m_Paddlesprite.getGlobalBounds().width < 600) {
    m_Paddlesprite.move(m_fStepX, 0);
  }
}