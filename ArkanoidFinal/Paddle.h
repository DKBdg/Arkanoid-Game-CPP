#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


enum Directions{Left = 0 , Right =1};
class Paddle
{
private: 
  sf::Sprite m_Paddlesprite;
  float m_fScaleX;
  float m_fStepX;
public:
  Paddle() {}
  Paddle(sf::Texture& texture, float Stepx, float xscale = 1);
  void UpdatePaddle(int i);
  float GetStepX() { return m_fStepX; }
  void SetPosition(float x, float y) { m_Paddlesprite.setPosition(x, y); }
  void SetTexture(sf::Texture& text) { m_Paddlesprite.setTexture(text); }
  void SetStep(float step) { m_fStepX = step; }
  void RenderPaddle(sf::RenderTarget* target) { target->draw(m_Paddlesprite); }
  sf::Sprite GetSprite() const { return m_Paddlesprite; }
};

