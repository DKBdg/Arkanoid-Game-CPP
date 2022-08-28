#include "Game.h"
void Game::InitBricks() {
  m_nBrickCount = 19 * 8;
  int randint = 0;
  for (int i = 0, XPos = 0, YPos = 4, rad = 0; i < m_nBrickCount; i++, XPos++) {
    randint = rnd() % 3;
    if (randint % 3 == 0)
      m_Tiles.push_back(SimpleTile(m_TextureMap["SimpleBrick"]));
    else if (randint % 3 == 1)
      m_Tiles.push_back(LightTile(m_TextureMap["LightBrick"]));
    else if (randint % 3 == 2)
      m_Tiles.push_back(HeavyTile(m_TextureMap["HeavyBrick"]));

    if (i % 19 == 0) { YPos++; XPos = 0; }
    m_Tiles[i].SetPosition(XPos * 32, YPos * 16);
  }
}
void Game::InitPaddle() {
  m_Paddle.SetTexture(m_TextureMap["SimplePaddle"]);
  m_Paddle.SetStep(6);
  m_Paddle.SetPosition(250.f, 500.f);
}
void Game::InitBall() {
  m_Ball.SetPosition(250.f, 490.f);
  m_Ball.SetTexture(m_TextureMap["SimpleBall"]);
  m_Ball.SetStepX(5);
  m_Ball.SetStepY(6);
  m_Ball.SetHp(4);
}
void Game::InitTextures()
{
  std::pair<std::string, sf::Texture> temp;
  temp.second = sf::Texture();


  temp.first = "SimpleBall";
  m_TextureMap.insert(temp);
  m_TextureMap["SimpleBall"].loadFromFile("Images/SimpleBall.png");

  temp.first = "SimplePaddle";
  m_TextureMap.insert(temp);
  m_TextureMap["SimplePaddle"].loadFromFile("Images/SimplePaddle.png");


  temp.first = "HeavyBrick";
  m_TextureMap.insert(temp);
  m_TextureMap["HeavyBrick"].loadFromFile("Images/HeavyBrick.png");

  temp.first = "LightBrick";
  m_TextureMap.insert(temp);
  m_TextureMap["LightBrick"].loadFromFile("Images/LightBrick.png");

  temp.first = "SimpleBrick";
  m_TextureMap.insert(temp);
  m_TextureMap["SimpleBrick"].loadFromFile("Images/SimpleBrick.png");

  temp.first = "ArkanoidImage";
  m_TextureMap.insert(temp);
  m_TextureMap["ArkanoidImage"].loadFromFile("Images/ArkanoidImage.png");

}
void Game::InitWindow() {
  m_Window = new sf::RenderWindow(sf::VideoMode(600, 600), "Arkanoid", sf::Style::Titlebar | sf::Style::Close);
  m_Window->setFramerateLimit(60);
}
void Game::InitMenu() {
  m_Menu.SetTexture(m_TextureMap["ArkanoidImage"]);
}
Game::Game() : m_Event(), m_bIsMenu(true)
{
  InitWindow();
  InitTextures();
  InitBall();
  InitPaddle();
  InitBricks();
  InitMenu();
}
void Game::UpdateBall() {
  if (m_Ball.GetHp() == 0)
    m_bIsMenu = true;
  else
    m_Ball.UpdateBall(m_Paddle, m_Tiles);
}
void Game::UpdateGameObj() {
  UpdatePaddle();
  UpdateBall();
  UpdateBrick();
}
void Game::RenderGameObj() {
  m_Window->clear();

  m_Paddle.RenderPaddle(m_Window);
  m_Ball.RenderBall(m_Window);
  for (auto item : m_Tiles) {
    item.Render(m_Window);
  }

  m_Window->display();
}
void Game::UpdatePaddle() {
  while (m_Window->pollEvent(m_Event)) {
    switch (m_Event.type) {
    case sf::Event::Closed:
      m_Window->close(); break;

    case sf::Event::KeyPressed:
      if (m_Event.key.code == sf::Keyboard::A) {
        m_Paddle.UpdatePaddle(Directions::Left);
        if (m_Ball.GetPauseTemp() && m_Paddle.GetSprite().getPosition().x > 0) {
          m_Ball.GetSprite().move(-m_Paddle.GetStepX(), 0);
        }
      }
      else if (m_Event.key.code == sf::Keyboard::D) {
        m_Paddle.UpdatePaddle(Directions::Right);
        if (m_Ball.GetPauseTemp() && m_Paddle.GetSprite().getPosition().x + m_Paddle.GetSprite().getGlobalBounds().width < 600) {
          m_Ball.GetSprite().move(m_Paddle.GetStepX(), 0);
        }
      }
      else if (m_Event.key.code == sf::Keyboard::Enter) {
        if (m_Ball.GetPauseTemp()) {
          m_Ball.SetPauseTemp(false);
        }
      }
      else if (m_Event.key.code == sf::Keyboard::Escape) {
        m_bIsMenu = true;
      }
      break;


    }
  }
}
void Game::UpdateBrick() {
  std::vector<Tile>::iterator item;
  for (item = begin(m_Tiles); item != end(m_Tiles); ++item) {

    if ((*item).GetSprite().getGlobalBounds().intersects(m_Ball.GetSprite().getGlobalBounds())) {
      (*item).SetHp((*item).GetHp() - 1);
      if ((*item).GetHp() == 0)
      {
        //m_Tiles.erase(item++);

        (*item).SetPosition(-100.f, -100.f);
      }
    }

  }


}
  void Game::RenderMenu() {
    m_Window->clear();

    if (m_Menu.GetCredits())
      m_Menu.CreditsDisplay(m_Window);
    else
      m_Menu.renderMenu(m_Window);

    m_Window->display();
  }
  void Game::LoadFromFile() {
    std::ifstream ifile;
    std::string TextureName;
    ifile.open("Save-Read.txt");
    int HpBall;
    (ifile >> HpBall).ignore();
    m_Ball.SetHp(HpBall);
    float StepX, StepY;
    (ifile >> StepX).ignore();
    (ifile >> StepY).ignore();
    m_Ball.SetStepX(StepX);
    m_Ball.SetStepY(StepY);
    float BallX, BallY;
    float PaddleX, PaddleY;
    (ifile >> BallX).ignore();
    (ifile >> BallY).ignore();
    (ifile >> PaddleX).ignore();
    (ifile >> PaddleY).ignore();
    m_Ball.SetPosition(BallX, BallY);
    m_Paddle.SetPosition(PaddleX, PaddleY);
    float TileX, TileY;
    int TileHp;
    for (int i = 0; i < m_nBrickCount; i++) {
      std::getline(ifile, TextureName);
      (ifile >> TileX).ignore();
      (ifile >> TileY).ignore();
      (ifile >> TileHp).ignore();
      m_Tiles[i].SetPosition(TileX, TileY);
      m_Tiles[i].SetHp(TileHp);
      m_Tiles[i].SetTexture(m_TextureMap[TextureName]);
    }
  }
  void Game::SaveToFile() {
    std::ofstream ofile;
    ofile.open("Save-Read.txt");
    ofile << m_Ball.GetHp() << std::endl;
    ofile << m_Ball.GetStepX() << std::endl;
    ofile << m_Ball.GetStepY() << std::endl;
    ofile << m_Ball.GetSprite().getPosition().x << std::endl;
    ofile << m_Ball.GetSprite().getPosition().y << std::endl;
    ofile << m_Paddle.GetSprite().getPosition().x << std::endl;
    ofile << m_Paddle.GetSprite().getPosition().y << std::endl;
    for (auto item : m_Tiles)
    {
      ofile << item.GetTextureName() << std::endl;
      ofile << item.GetSprite().getPosition().x << std::endl;
      ofile << item.GetSprite().getPosition().y << std::endl;
      ofile << item.GetHp() << std::endl;
    }
  }
  void Game::UpdateMenu() {
    while (m_Window->pollEvent(m_Event)) {
      switch (m_Event.type) {
      case sf::Event::Closed:
        m_Window->close(); break;
      case sf::Event::KeyPressed: {
        if (m_Event.key.code == sf::Keyboard::W) {
          m_Menu.UpdateMenu(DirectionMenu::Up);
        }
        else if (m_Event.key.code == sf::Keyboard::S) {
          m_Menu.UpdateMenu(DirectionMenu::Down);
        }
        else if (m_Event.key.code == sf::Keyboard::Enter) {
          switch (m_Menu.UpdateMenu(DirectionMenu::Enter)) {
          case 0:
            NewGameStart();
            m_bIsMenu = false;
            break;
          case 1:
            LoadFromFile();
            m_bIsMenu = false;
            break;
          case 2:
            SaveToFile();
            break;
          case 3:
            m_Window->close();
            break;
          case 4:
            m_Menu.SetCredits(true);
            break;
          case 5:
            m_bIsMenu = false;
            break;
          }

        }
        else if (m_Event.key.code == sf::Keyboard::Escape) {
          if (m_Menu.GetCredits())
          {
            m_Menu.SetCredits(false);
          }
          else {
            m_Window->close();
          }
        }
      }
      }
    }
  }

  void Game::NewGameStart() {
    m_Ball.SetPosition(250.f, 490.f);
    m_Ball.SetStepX(5);
    m_Ball.SetStepY(6);
    m_Ball.SetHp(4);
    m_Paddle.SetStep(6);
    m_Paddle.SetPosition(250.f, 500.f);
    m_Tiles.clear();
    m_nBrickCount = 19 * 8;
    int randint = 0;
    for (int i = 0, XPos = 0, YPos = 4, rad = 0; i < m_nBrickCount; i++, XPos++) {
      randint = rnd() % 3;
      if (randint % 3 == 0)
        m_Tiles.push_back(SimpleTile(m_TextureMap["SimpleBrick"]));
      else if (randint % 3 == 1)
        m_Tiles.push_back(LightTile(m_TextureMap["LightBrick"]));
      else if (randint % 3 == 2)
        m_Tiles.push_back(HeavyTile(m_TextureMap["HeavyBrick"]));

      if (i % 19 == 0) { YPos++; XPos = 0; }
      m_Tiles[i].SetPosition(XPos * 32, YPos * 16);
    }
  }
  void Game::StartMenu() {
    while (m_Window->isOpen() && IsMenu()) {

      RenderMenu();

      UpdateMenu();

    }



  }
  void Game::GameLogic() {
    while (m_Window->isOpen())
    {
      StartMenu();
      UpdateGameObj();
      RenderGameObj();
    }
  }