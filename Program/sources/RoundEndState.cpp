#include "../headers/RoundEndState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/Config.hpp"
#include "../headers/FontManager.hpp"
#include "../headers/Game.hpp"
#include "../headers/GameState.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/Match.hpp"
#include "../headers/MatchState.hpp"
#include "../headers/Player.hpp"
#include "../headers/TextureManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <sstream>

const std::string RoundEndState::m_roundID = "ROUND";

void RoundEndState::update(){
  std::cout<< "score : "<<Game::getInstance()->getMatch()->getPlayer1()->getPoints() << "/" <<Game::getInstance()->getMatch()->getPlayer2()->getPoints() << std::endl;
  while(Game::getInstance()->getTime() < 5.);
  if(Game::getInstance()->getMatch()->isFinished() ){
    Game::getInstance()->getStateHandler()->change(new CharacterState() );
  }else{
    Game::getInstance()->getStateHandler()->change(new MatchState() );
  }
}

void RoundEndState::render(){
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  //score displaying
  s.setTexture(*t);
  displayScore(&s);
  m_window->draw();
}

bool RoundEndState::enter(){
  m_render = Game::getInstance()->getRender();
  m_container = new Container(m_render );
  m_window = new GUIWindow (Game::getInstance()->getWindow(), m_container);
  sf::Sprite s, s2;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  //score displaying
  s2.setTexture(*t);
  displayScore(&s2);
  //collapse screen
  t = TextureManager::getInstance()->get("loading")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(0, 0, 800, 200) );
  s.setPosition(0, 400);
  m_render->draw(s);
  m_window->draw();
  int dec = 0;
  Game::getInstance()->getClock()->restart();
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    displayScore(&s2);
    s.setPosition(dec, 0);
    m_render->draw(s);
    s.setPosition(0, 200);
    m_render->draw(s);
    s.setPosition(0, 400);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  dec = 0;
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    displayScore(&s2);
    s.setPosition(-dec, 200);
    m_render->draw(s);
    s.setPosition(0, 400);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  dec = 0;
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    displayScore(&s2);
    s.setPosition(dec, 400);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  return true;
}

bool RoundEndState::exit(){
  //if we already did the number of rounds, the match ends
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("loading")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(0, 0, 80, 200) );
  m_render->draw(s);
  m_window->draw();
  int dec = 0;
  Game::getInstance()->getClock()->restart();
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    s.setPosition(dec, 0);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  dec = 800;
  while(dec >= 0){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    s.setPosition(dec, 200);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec -= 80;
    Game::getInstance()->getClock()->restart();
  }
  dec = 0;
  while(dec <= 800){
    if(Game::getInstance()->getMsTime() < 1 )
      continue;
    s.setPosition(dec, 400);
    m_render->draw(s);
    m_window->draw();
    Game::getInstance()->display();
    dec += 80;
    Game::getInstance()->getClock()->restart();
  }
  // end displaying
  return true;
}

void RoundEndState::deleteAll(){
  delete m_container;
  m_container = NULL;
  delete m_window;
  m_window = NULL;
}

void RoundEndState::displayScore(sf::Sprite * s){
  m_render->clear(sf::Color(120, 120, 120) );
  std::ostringstream oss;
  Match * m = Game::getInstance()->getMatch();
  //frame
  sf::RectangleShape r(sf::Vector2f(640, 480) );
  r.setPosition(80, 100);
  r.setFillColor(sf::Color(110, 110, 110) );
  r.setOutlineThickness(4);
  r.setOutlineColor(sf::Color::Black );
  m_render->draw(r);
  r.setSize(sf::Vector2f(0, 480) );
  r.setPosition(400, 100);
  m_render->draw(r);
  r.setSize(sf::Vector2f(640, 0) );
  r.setPosition(80, 400);
  m_render->draw(r);
  r.setSize(sf::Vector2f(640, 0) );
  r.setPosition(80, 220);
  m_render->draw(r);
  //Round count
  sf::Text t;
  t.setFont(*FontManager::getInstance()->get(DEFAULT_FONT) );
  t.setColor(sf::Color::Black);
  t.setCharacterSize(50);
  oss.str("");
  oss.clear();
  oss << "Round " << m->getCurrentRound() << "/" << m->getRoundsNumber();
  t.setString(oss.str() );
  t.setOrigin(t.getLocalBounds().width/2, t.getLocalBounds().height/2);
  t.setPosition(400, 45);
  m_render->draw(t);
  //players's names
  t.setString(m->getPlayer1()->getName() );
  t.setOrigin(t.getLocalBounds().width/2, t.getLocalBounds().height/2);
  t.setPosition(240, 160);
  m_render->draw(t);
  t.setPosition(800-240, 160);
  t.setString(m->getPlayer2()->getName());
  m_render->draw(t);
  //global score
  oss.str("");
  oss.clear();
  oss << m->getPlayer1()->getVictories();
  t.setPosition(240, 260);
  t.setString( oss.str() );
  m_render->draw(t);
  t.setPosition(800-240, 260); 
  oss.str("");
  oss.clear();
  oss << m->getPlayer2()->getVictories();
  t.setString(oss.str() );
  m_render->draw(t);
  //local score
  t.setPosition(240, 370); 
  oss.str("");
  oss.clear();
  oss << m->getPlayer1()->getPoints();
  t.setString( oss.str() );
  m_render->draw(t);
  t.setPosition(800-240, 370);
  oss.str("");
  oss.clear();
  oss << m->getPlayer2()->getPoints();
  t.setString(oss.str() );
  m_render->draw(t);
  
}
