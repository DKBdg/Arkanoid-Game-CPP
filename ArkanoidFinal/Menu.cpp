#include "Menu.h"
Menu::Menu() {
  m_bCreditsDisplay = false;
  m_End.push_back("Thank you for playin' this game");
  m_End.push_back(",hope you enjoyed it");
  m_End.push_back("Fayaz");
  m_nActMem = 0;
  m_Font.loadFromFile("Fonts/Raleway-Regular.ttf");
  m_TextStr.setFont(m_Font);
  m_TextStr.setCharacterSize(24);
  m_TextStr.setFillColor(sf::Color::White);
  m_To_Be_Printed.push_back("Start a New Game");
  m_To_Be_Printed.push_back("Load");
  m_To_Be_Printed.push_back("Save");
  m_To_Be_Printed.push_back("Exit");
  m_To_Be_Printed.push_back("Credits");
  m_To_Be_Printed.push_back("Continue");
  m_fSpriteXPos = 200, m_fSpriteYPos = 120;
  m_fXPos = 200;
  m_fYPos = 200;
  m_TextStr.setPosition(m_fXPos, m_fYPos);
  m_TextStr.setString(m_To_Be_Printed[0]);

}
void Menu::SetTexture(sf::Texture& texture) {
  m_ArkanoidImage.setTexture(texture);
}
void Menu::CreditsDisplay(sf::RenderTarget* target) {

  for (int i = 0; i < m_End.size(); i++) {
    m_TextStr.setString(m_End[i]);
    m_TextStr.setPosition(m_fXPos, m_fYPos + 40 * i);
    target->draw(m_TextStr);
  }


}
void Menu::renderMenu(sf::RenderTarget* target) {
  m_ArkanoidImage.setPosition(m_fSpriteXPos, m_fSpriteYPos);
  target->draw(m_ArkanoidImage);
  for (int i = 0; i < m_To_Be_Printed.size(); i++) {
    m_TextStr.setPosition(m_fXPos, m_fYPos + 40 * i);
    m_TextStr.setString(m_To_Be_Printed[i]);
    if (i == m_nActMem) {
      m_TextStr.setFillColor(sf::Color::Blue);
      target->draw(m_TextStr);
      m_TextStr.setFillColor(sf::Color::White);
    }
    else
    {
      target->draw(m_TextStr);
    }

  }
}
int Menu:: UpdateMenu(int i) {
  if (i == DirectionMenu::Up) {
    if (m_nActMem > 0)
      m_nActMem--;
    else
      m_nActMem = m_To_Be_Printed.size() - 1;
  }
  else if (i == DirectionMenu::Down) {
    if (m_nActMem < m_To_Be_Printed.size() - 1)
      m_nActMem++;
    else
      m_nActMem = 0;

  }
  else if (i == DirectionMenu::Enter) {
    return m_nActMem;
  }
  return 0;
}