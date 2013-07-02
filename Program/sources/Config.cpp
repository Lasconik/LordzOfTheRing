#include "../headers/Config.hpp"
#include "../headers/Action.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

//TODO complete default input
void Config::init(){
  m_musicVolume = 70;
  m_soundVolume = 100;
  m_windowWidth = 300;
  m_windowHeight = 100;
  m_mapping[sf::Keyboard::Escape] = actionToByte(NAction::PAUSE);
  m_mapping[sf::Keyboard::A] = actionToByte(NAction::ATTACK_LEFT, NAction::PLAYER1, NAction::PLAYER2);
  m_mapping[sf::Keyboard::Z] = actionToByte(NAction::ATTACK_MIDDLE, NAction::PLAYER1, NAction::PLAYER2);
  m_mapping[sf::Keyboard::E] = actionToByte(NAction::ATTACK_RIGHT, NAction::PLAYER1, NAction::PLAYER2);
  m_mapping[sf::Keyboard::Q] = actionToByte(NAction::DODGE_LEFT, NAction::PLAYER1, NAction::PLAYER1);
  m_mapping[sf::Keyboard::S] = actionToByte(NAction::DODGE_MIDDLE, NAction::PLAYER1, NAction::PLAYER1);
  m_mapping[sf::Keyboard::D] = actionToByte(NAction::DODGE_RIGHT, NAction::PLAYER1, NAction::PLAYER1);
  m_mapping[sf::Keyboard::I] = actionToByte(NAction::ATTACK_LEFT, NAction::PLAYER2, NAction::PLAYER1);
  m_mapping[sf::Keyboard::O] = actionToByte(NAction::ATTACK_MIDDLE, NAction::PLAYER2, NAction::PLAYER1);
  m_mapping[sf::Keyboard::P] = actionToByte(NAction::ATTACK_RIGHT, NAction::PLAYER2, NAction::PLAYER1);
  m_mapping[sf::Keyboard::K] = actionToByte(NAction::DODGE_LEFT, NAction::PLAYER2, NAction::PLAYER2);
  m_mapping[sf::Keyboard::L] = actionToByte(NAction::DODGE_MIDDLE, NAction::PLAYER2, NAction::PLAYER2);
  m_mapping[sf::Keyboard::M] = actionToByte(NAction::DODGE_RIGHT, NAction::PLAYER2, NAction::PLAYER2);
}


/** Retrieves first int after the first '=' */
unsigned int extractInt(const std::string& s){
  return atoi( cutFrom(s, '=').c_str() );
}

bool Config::loadFromFile(const std::string& path){
  init();
  std::ifstream ifs;
  ifs.open(path.c_str() );
  if( !ifs.good() ){
    return false;
  }
  std::string line = "";
  while( !ifs.eof() ){
    getline(ifs, line);
    if(line[0] == '#' )
      continue;
    if(contains(line, "width") ){
      m_windowWidth = extractInt(line);
      continue;
    }
    if(contains(line, "height=")  ){
      m_windowHeight = extractInt(line);
      continue;
    }
    if(contains(line, "music=") ){
      setMusicVolume( extractInt(line) );
      continue;
    }
    if(contains(line,"sound=") ){
      setSoundVolume( extractInt(line) );
      continue;
    }
    if(contains(line, "pause=") ){
      setAction( (Key) extractInt(line), 
		 NAction::actionToByte(NAction::PAUSE) );
      continue;
    }
    //Player 1 controller
    if(contains(line, "1-attackL=") ){
      setAction( (Key) extractInt(line), 
NAction::actionToByte(NAction::ATTACK_LEFT, NAction::PLAYER1, NAction::PLAYER2) );
      continue;
    }
    if(contains(line, "1-attackM=") ){
      setAction( (Key) extractInt(line), 
NAction::actionToByte(NAction::ATTACK_MIDDLE, NAction::PLAYER1, NAction::PLAYER2) );
      continue;
    }
    if(contains(line, "1-attackR=") ){
      setAction( (Key) extractInt(line), 
 NAction::actionToByte(NAction::ATTACK_RIGHT, NAction::PLAYER1, NAction::PLAYER2) );
      continue;
    }
    if(contains(line, "1-dodgeL=") ){
      setAction( (Key) extractInt(line), 
NAction::actionToByte(NAction::DODGE_LEFT, NAction::PLAYER1, NAction::PLAYER1) );
      continue;
    }
    if(contains(line, "1-dodgeM=") ){
      setAction( (Key) extractInt(line), 
 NAction::actionToByte(NAction::DODGE_MIDDLE, NAction::PLAYER1, NAction::PLAYER1) );
      continue;
    }
    if(contains(line, "1-dodgeR=") ){
      setAction( (Key) extractInt(line), 
 NAction::actionToByte(NAction::DODGE_RIGHT, NAction::PLAYER1, NAction::PLAYER1) );
      continue;
    }
    //player2 controller
        if(contains(line, "2-attackL=") ){
      setAction( (Key) extractInt(line), 
NAction::actionToByte(NAction::ATTACK_LEFT, NAction::PLAYER2, NAction::PLAYER1) );
      continue;
    }
    if(contains(line, "2-attackM=") ){
      setAction( (Key) extractInt(line), 
NAction::actionToByte(NAction::ATTACK_MIDDLE, NAction::PLAYER2, NAction::PLAYER1) );
      continue;
    }
    if(contains(line, "2-attackR=") ){
      setAction( (Key) extractInt(line), 
 NAction::actionToByte(NAction::ATTACK_RIGHT, NAction::PLAYER2, NAction::PLAYER1) );
      continue;
    }
    if(contains(line, "2-dodgeL=") ){
      setAction( (Key) extractInt(line), 
NAction::actionToByte(NAction::DODGE_LEFT, NAction::PLAYER2, NAction::PLAYER2) );
      continue;
    }
    if(contains(line, "2-dodgeM=") ){
      setAction( (Key) extractInt(line), 
 NAction::actionToByte(NAction::DODGE_MIDDLE, NAction::PLAYER2, NAction::PLAYER2) );
      continue;
    }
    if(contains(line, "2-dodgeR=") ){
      setAction( (Key) extractInt(line), 
 NAction::actionToByte(NAction::DODGE_RIGHT, NAction::PLAYER2, NAction::PLAYER2) );
      continue;
    }
  }
  std::cout<<toString() <<std::endl;
  return true;
}

action Config::getAction(const Key& k){
  if( m_mapping.find(k) == m_mapping.end() )
    return (action)0;
  return m_mapping[k];
}

//TODO
Key Config::getKey(const action& a) const{
  return (Key)-1;
}

void Config::setAction(const Key& k, const action& a){
  std::map<Key,action>::iterator it = m_mapping.find(k);
  if( it != m_mapping.end() )
    m_mapping.erase( it );
  m_mapping.insert( std::pair<Key, action>(k, a) );
}

//TODO
std::string Config::toString(){
  std::ostringstream oss;
  oss << "Resolution : "<< m_windowWidth <<"x"<< m_windowHeight<< std::endl;
  oss << "Volume - Music : "<< (unsigned int)m_musicVolume<<" Sound : "<< (unsigned int)m_soundVolume<< std::endl;
  oss << "Key mapping : "<< std::endl;
  std::map<Key,action>::iterator it;
  for (it = m_mapping.begin(); it != m_mapping.end(); ++it) {
    oss << (int)it->first << " : ";
    if(NAction::getDoer(it->second) == NAction::PLAYER1){
      oss << "Player1 - ";
    }else{
      oss << "Player2 - ";
    }
    switch( NAction::getAction(it->second) ){
    case NAction::ATTACK_LEFT: oss << "Attack Left"; break;
    case NAction::ATTACK_MIDDLE: oss << "Uppercut"; break;
    case NAction::ATTACK_RIGHT: oss << "Attack Right"; break;
    case NAction::DODGE_LEFT: oss << "Dodge Left"; break;
    case NAction::DODGE_MIDDLE: oss << "Dodge Middle"; break;
    case NAction::DODGE_RIGHT: oss << "Dodge Right"; break;
    case NAction::PAUSE: oss << "Pause"; break;
    default: oss << "Unknown"; break;
    }
    oss << " ("<< (unsigned int)NAction::getAction(it->second) <<")"<<std::endl;
    
  }
  return oss.str();
}
