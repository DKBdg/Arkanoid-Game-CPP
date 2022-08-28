#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <map>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>
#include "TIle.h"
#include "Paddle.h"
#include "Ball.h"
#include "Menu.h"


class Game
{
private:


  //Gaeme Objects
  Menu m_Menu;

  std::vector<Tile> m_Tiles;
  int m_nBrickCount;
  Paddle m_Paddle;
  Ball m_Ball;
  std::map<std::string, sf::Texture> m_TextureMap;



  bool m_bIsMenu;


  std::random_device rnd;

  //Essentials for the Canvas
  sf::RenderWindow* m_Window;
  sf::Event m_Event;


  void InitBricks();
  void InitPaddle();
  void InitBall();
  void InitTextures();
  void InitWindow();
  void InitMenu();
  


public:
  Game();
  void UpdateBall();

  void UpdateGameObj();

  void RenderGameObj();
  void UpdatePaddle();

  void UpdateBrick();
  void RenderMenu();
  void LoadFromFile();
  void SaveToFile();
  void UpdateMenu();

  void NewGameStart();

  bool IsMenu() { return m_bIsMenu; }
  void StartMenu();
  void GameLogic();
  ~Game() {
    delete m_Window;
  }

};

