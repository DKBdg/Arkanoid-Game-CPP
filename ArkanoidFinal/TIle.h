#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Tile
{
protected: 
  std::string TextureName;
  int m_nHp;
  sf::Sprite m_TileSprite;
public:
  Tile(){}
  Tile(sf::Sprite sprite, int hp): m_nHp(hp) { m_TileSprite = sprite; }
  int GetHp() const { return m_nHp; }
  void SetHp(int hp)  { m_nHp = hp; }
  void Render(sf::RenderTarget* target) { target->draw(m_TileSprite); }
  void SetTexture(sf::Texture& a) { m_TileSprite.setTexture(a); }
  void SetPosition(float x, float y) { m_TileSprite.setPosition(x, y); }
  sf::Sprite GetSprite() const { return m_TileSprite; }
  std::string GetTextureName() const { return TextureName; }
  virtual ~Tile(){}
};


class LightTile:virtual public Tile  {
public:
  LightTile(){}
  LightTile(sf::Texture& texture) { m_nHp = 2; m_TileSprite.setTexture(texture); TextureName = "LightBrick"; }
};
class HeavyTile : virtual public Tile {
public:
  HeavyTile(){}
  HeavyTile(sf::Texture& texture) { m_nHp = 4; m_TileSprite.setTexture(texture); TextureName = "HeavyBrick";
  }

};
class SimpleTile : virtual public Tile {
public:
  SimpleTile(){}
  SimpleTile(sf::Texture& texture) { m_nHp = 1; m_TileSprite.setTexture(texture); TextureName = "SimpleBrick";
  }

};



