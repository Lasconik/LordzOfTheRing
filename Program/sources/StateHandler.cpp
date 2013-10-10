#include "../headers/StateHandler.hpp"
#include "../headers/Game.hpp"
#include "../headers/GameState.hpp"
#include "../headers/CharacterState.hpp"
#include "../headers/MainMenuState.hpp"
#include "../headers/MatchState.hpp"
#include "../headers/OptionState.hpp"
#include "../headers/SettingsState.hpp"
#include "../headers/RoundEndState.hpp"


//#include <iostream> //delete
#include <vector>


void StateHandler::push(GameState * s){
  m_states.push_back(s);
  m_states.back()->enter();
}

void StateHandler::change(GameState * s){
  GameState * g = NULL;
  if(!m_states.empty() ){
    if(m_states.back()->getID().compare( s->getID() ) == 0){
      return;
    }
    if(m_states.back()->exit() ){
      g = m_states.back();
      m_states.pop_back();
    }
  }
  m_states.push_back(s);
  m_states.back()->enter();
  if(g != NULL){
    g->deleteAll(); // useless ?
    if( ! g->getID().compare("MAIN_MENU") ){
      delete (MainMenuState *)g;
      return;
    }
    if( ! g->getID().compare("CHAR_MENU") ){
      delete (CharacterState *)g;
      return;
    }
    if( ! g->getID().compare("MATCH") ){
      delete (MatchState *)g;
      return;
    }
    if( ! g->getID().compare("ROUND") ){
      delete (RoundEndState *)g;
      return;
    }
    if( ! g->getID().compare("SETTINGS") ){
      delete (SettingsState *)g;
      return;
    }
    if( ! g->getID().compare("OPTION_MENU") ){
      delete (OptionState *)g;
      return;
    }
  }
}

void StateHandler::pop(){
  if(!m_states.empty() ){
    if(m_states.back() ->exit() ){
      delete m_states.back();
      m_states.pop_back();
    }
  }
}

void StateHandler::update(){
  std::cout<<"update ? "<<Game::getInstance()->updating()<<std::endl;
  if(Game::getInstance()->updating() && !m_states.empty() )
    m_states.back()->update();
}

void StateHandler::render(){
  std::cout<<"render ? "<<Game::getInstance()->updating()<<std::endl;
  if(Game::getInstance()->updating() && !m_states.empty() )
    m_states.back()->render();
}
