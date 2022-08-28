#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <string>
#include <iostream>
enum DirectionMenu { Up = 1, Down = 0 ,Enter=2};
class Menu
{
private:
  bool m_bCreditsDisplay;
  sf::Sprite m_ArkanoidImage;
  sf::Font m_Font;
  sf::Text m_TextStr;
  std::vector<std::string> m_To_Be_Printed;
  std::vector<std::string> m_End;
  float m_fSpriteXPos, m_fSpriteYPos;
  float m_fXPos, m_fYPos;
  int m_nActMem;
 public:
   Menu();
   void SetTexture(sf::Texture& texture);
   void CreditsDisplay(sf::RenderTarget* target);
   void SetCredits(bool a) { m_bCreditsDisplay = a; }
   bool GetCredits() const { return m_bCreditsDisplay; }
   int GetActMem() const { return m_nActMem; }
   void renderMenu(sf::RenderTarget* target);
   int UpdateMenu(int i);




};

