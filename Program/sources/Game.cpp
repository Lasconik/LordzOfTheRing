/**
   Here is the game singleton : in which state we are, how many times since launching, the window...
*/
#include "../headers/Game.hpp"
#include "../headers/Action.hpp"
#include "../headers/Character.hpp"
#include "../headers/CharacterManager.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Config.hpp"
#include "../headers/GameState.hpp"
#include "../headers/MainMenuState.hpp"
#include "../headers/Match.hpp"
#include "../headers/Misc.hpp"
//#include "../headers/Music.hpp"
//#include "../headers/MusicManager.hpp"
#include "../headers/Player.hpp"
#include "../headers/ResourceManager.hpp"
#include "../headers/SpritesheetManager.hpp"
#include "../headers/StateHandler.hpp"
#include "../headers/Texture.hpp"
#include "../headers/TextureManager.hpp"
#include "../headers/GUI_Bordered.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/FontManager.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>


#include <cstdio> //DELETE
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>


/** init all required the game : 
    -loads configuration
    -creates the window
    -loads files
    -initialize default players, characters, matches...
    -begins the loop
**/
void Game::init(){
 
  m_window = new sf::RenderWindow(sf::VideoMode(Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() ), "MyBadPunchOut"); 
  m_window->setFramerateLimit( (float) FRAMERATE);
  m_window->setPosition(sf::Vector2i(10, 10) ); //adjust
  m_render->create(Config::getInstance()->getWindowWidth(), Config::getInstance()->getWindowHeight() );
  //starting loop
  m_stateHandler->change(new MainMenuState() );
  m_music->setVolume(Config::getInstance()->getMusicVolume() );
  m_music->openFromFile("../../resources/audio/menu1.ogg");
  m_music->setVolume(Config::getInstance()->getMusicVolume() );
  m_music->play();
  loop();
}

void Game::start(){
  //setState(GameState::SPLASH);
  m_render = new sf::RenderTexture();
  m_stateHandler = new StateHandler();
  m_clock = new sf::Clock();
  m_timer = new sf::Time();
  m_music = new sf::Music();
  Player p1("Aaron");
  Player p2("Barney");
  m_match = new Match(&p1, &p2, 90, 3);
  splash();
}

/** Starts the game loop : 
    -read input
    -eval action
    -print situation
**/
void Game::loop(){
  std::cout<<"looping"<<std::endl;
  while(m_window->isOpen() ){
    m_window->clear(sf::Color::Black);
    m_stateHandler->update();
    m_stateHandler->render();
    m_window->display();
  }
}


void Game::splash(){
  sf::RenderWindow rw(sf::VideoMode(600, 400), "splashscreen", sf::Style::None );
  rw.setPosition(sf::Vector2i(0,0) ); //adjust
  sf::Texture * t;
  t = TextureManager::getInstance()->get("splashscreens/sfml.splash")->getTexture();
  sf::Sprite s;
  s.setTexture(*t);
  s.setOrigin(t->getSize().x/2, t->getSize().y/2);
  s.setPosition(sf::Vector2f(300, 200) );
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 2.);
  t = TextureManager::getInstance()->get("splashscreens/auth.splash")->getTexture();
  s.setTexture(*t );
  s.setOrigin(t->getSize().x/2, t->getSize().y/2);
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 4.);
  t = TextureManager::getInstance()->get("splashscreens/pixotters.splash")->getTexture();
  s.setTexture(*t );
  s.setOrigin(t->getSize().x/2, t->getSize().y/2);
  rw.clear(sf::Color::White);
  rw.draw(s);
  rw.display();
  while(getTime() < 6.);
  rw.close();
  TextureManager::getInstance()->remove("splashscreens/sfml.splash");
  TextureManager::getInstance()->remove("splashscreens/auth.splash");
  
  init();
}  


void Game::pause(const sf::Int64& t0){
  sf::Event event;
  while( m_window->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      close();
    }else if(event.type ==sf::Event::KeyPressed ){
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(Action::getType(a) == Action::PAUSE ){
	Game::getInstance()->getStateHandler()->pop();
	*m_timer = sf::microseconds(t0);
	break;
      }
    }
  }
}

/** Closes the game
 **/
void Game::close(){
  TextureManager::getInstance()->remove("background.png");
  TextureManager::getInstance()->remove("sprites.png");
  m_window->close();
  delete m_music;
  delete m_timer;
  delete m_clock;
  delete m_match;
  delete m_stateHandler;
  delete m_render;
  delete m_window;
}



int main(){
  Game::getInstance()->start();
  return 0;
}

