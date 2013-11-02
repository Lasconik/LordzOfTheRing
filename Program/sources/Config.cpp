#include "../headers/Config.hpp"
#include "../headers/Action.hpp"
#include "../headers/ResourcesDirectories.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include <iostream> //delete

void Config::init(){
  m_musicVolume = 70;
  m_soundVolume = 100;
  m_windowWidth = 300;
  m_windowHeight = 100;
  m_mapping[sf::Keyboard::Escape] = actionToByte(Action::PAUSE);
  m_mapping[sf::Keyboard::A] = actionToByte(Action::ATTACK_LEFT, Action::PLAYER1, Action::PLAYER2);
  m_mapping[sf::Keyboard::Z] = actionToByte(Action::ATTACK_MIDDLE, Action::PLAYER1, Action::PLAYER2);
  m_mapping[sf::Keyboard::E] = actionToByte(Action::ATTACK_RIGHT, Action::PLAYER1, Action::PLAYER2);
  m_mapping[sf::Keyboard::Q] = actionToByte(Action::DODGE_LEFT, Action::PLAYER1, Action::PLAYER1);
  m_mapping[sf::Keyboard::S] = actionToByte(Action::DODGE_MIDDLE, Action::PLAYER1, Action::PLAYER1);
  m_mapping[sf::Keyboard::D] = actionToByte(Action::DODGE_RIGHT, Action::PLAYER1, Action::PLAYER1);
  m_mapping[sf::Keyboard::I] = actionToByte(Action::ATTACK_LEFT, Action::PLAYER2, Action::PLAYER1);
  m_mapping[sf::Keyboard::O] = actionToByte(Action::ATTACK_MIDDLE, Action::PLAYER2, Action::PLAYER1);
  m_mapping[sf::Keyboard::P] = actionToByte(Action::ATTACK_RIGHT, Action::PLAYER2, Action::PLAYER1);
  m_mapping[sf::Keyboard::K] = actionToByte(Action::DODGE_LEFT, Action::PLAYER2, Action::PLAYER2);
  m_mapping[sf::Keyboard::L] = actionToByte(Action::DODGE_MIDDLE, Action::PLAYER2, Action::PLAYER2);
  m_mapping[sf::Keyboard::M] = actionToByte(Action::DODGE_RIGHT, Action::PLAYER2, Action::PLAYER2);
}


bool Config::loadFromFile(const std::string& path){
  init();
  std::ifstream ifs;
  ifs.open(ResDir::getResDir()+path );
  if( !ifs.good() ){
    return false;
  }
  std::string line = "";
  m_windowWidth = 800;
  m_windowHeight = 600;
  setAction( (Key) 36, 
		 Action::actionToByte(Action::PAUSE) );
  while( !ifs.eof() ){
    getline(ifs, line);
    if(line[0] == '#' )
      continue;
    if(contains(line, "width=") ){
      m_windowWidth = 800;
      continue;
    }
    if(contains(line, "height=")  ){
      m_windowHeight = 600;
      continue;
    }
    if(contains(line, "fullscreen=")  ){
      int full = extractInt(line);
      if(full == 0)
	m_fullscreen = false;
      else
	m_fullscreen = true;
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
    //Player 1 controller
    if(contains(line, "1-attackL=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::ATTACK_LEFT, Action::PLAYER1, Action::PLAYER2) );
      continue;
    }
    if(contains(line, "1-attackM=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::ATTACK_MIDDLE, Action::PLAYER1, Action::PLAYER2) );
      continue;
    }
    if(contains(line, "1-attackR=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::ATTACK_RIGHT, Action::PLAYER1, Action::PLAYER2) );
      continue;
    }
    if(contains(line, "1-dodgeL=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::DODGE_LEFT, Action::PLAYER1, Action::PLAYER1) );
      continue;
    }
    if(contains(line, "1-dodgeM=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::DODGE_MIDDLE, Action::PLAYER1, Action::PLAYER1) );
      continue;
    }
    if(contains(line, "1-dodgeR=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::DODGE_RIGHT, Action::PLAYER1, Action::PLAYER1) );
      continue;
    }
    //player2 controller
    if(contains(line, "2-attackL=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::ATTACK_LEFT, Action::PLAYER2, Action::PLAYER1) );
      continue;
    }
    if(contains(line, "2-attackM=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::ATTACK_MIDDLE, Action::PLAYER2, Action::PLAYER1) );
      continue;
    }
    if(contains(line, "2-attackR=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::ATTACK_RIGHT, Action::PLAYER2, Action::PLAYER1) );
      continue;
    }
    if(contains(line, "2-dodgeL=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::DODGE_LEFT, Action::PLAYER2, Action::PLAYER2) );
      continue;
    }
    if(contains(line, "2-dodgeM=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::DODGE_MIDDLE, Action::PLAYER2, Action::PLAYER2) );
      continue;
    }
    if(contains(line, "2-dodgeR=") ){
      setAction( (Key) extractInt(line), 
		 Action::actionToByte(Action::DODGE_RIGHT, Action::PLAYER2, Action::PLAYER2) );
      continue;
    }
  }
  return true;
}


bool Config::saveFile(const std::string& f){
  std::ofstream ofs(ResDir::getResDir()+f);
  //  ofs.open(f.c_str() );
  if( !ofs.good() ){
    return false;
  }
  ofs << "#fullscreen"<<std::endl;
  ofs.flush();
  ofs << "fullscreen=";
  if(m_fullscreen)
    ofs<<"1";
  else
    ofs<<"0";
  ofs<<std::endl;
  ofs.flush();
  ofs<<"#sound (in percents)"<<std::endl<<"music="<<(unsigned int)m_musicVolume<<std::endl;
  ofs.flush();
  ofs<<"sound="<<(unsigned int)m_soundVolume<<std::endl;
  ofs.flush();
  action a;
  ofs<<"#player 1 inputs"<<std::endl;
  ofs.flush();
  a = actionToByte(Action::ATTACK_LEFT, Action::PLAYER1, Action::PLAYER2);
  ofs<<"1-attackL="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::ATTACK_MIDDLE, Action::PLAYER1, Action::PLAYER2);
  ofs<<"1-attackM="<<(int)(getKey(a) )<<std::endl;
    ofs.flush();
a = actionToByte(Action::ATTACK_RIGHT, Action::PLAYER1, Action::PLAYER2);
  ofs<<"1-attackR="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::DODGE_LEFT, Action::PLAYER1, Action::PLAYER1);
  ofs<<"1-dodgeL="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::DODGE_MIDDLE, Action::PLAYER1, Action::PLAYER1);
  ofs<<"1-dodgeM="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::DODGE_RIGHT, Action::PLAYER1, Action::PLAYER1);
  ofs<<"1-dodgeR="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  ofs<<"#player 2 inputs"<<std::endl;
  ofs.flush();
  a = actionToByte(Action::ATTACK_LEFT, Action::PLAYER2, Action::PLAYER1);
  ofs<<"2-attackL="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::ATTACK_MIDDLE, Action::PLAYER2, Action::PLAYER1);
  ofs<<"2-attackM="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::ATTACK_RIGHT, Action::PLAYER2, Action::PLAYER1);
  ofs<<"2-attackR="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::DODGE_LEFT, Action::PLAYER2, Action::PLAYER2);
  ofs<<"2-dodgeL="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::DODGE_MIDDLE, Action::PLAYER2, Action::PLAYER2);
  ofs<<"2-dodgeM="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  a = actionToByte(Action::DODGE_RIGHT, Action::PLAYER2, Action::PLAYER2);
  ofs<<"2-dodgeR="<<(int)(getKey(a) )<<std::endl;
  ofs.flush();
  ofs.close();
  return true;
}

action Config::getAction(const Key& k){
  if( m_mapping.find(k) == m_mapping.end() )
    return (action)0;
  return m_mapping[k];
}

Key Config::getKey(const action& a) const{
  //std::map<Key,action>::iterator it;
  // show content:
  for (auto it=m_mapping.begin(); it!=m_mapping.end(); ++it)
    if(it->second == a)
      return it->first;
      
  return (Key)-1;
}

void Config::setAction(const Key& k, const action& a){
  std::map<Key,action>::iterator it = m_mapping.find(k);
  if( it != m_mapping.end() )
    m_mapping.erase( it );
  m_mapping.insert( std::pair<Key, action>(k, a) );
}


void Config::dropAction(const action& a){
  auto it = m_mapping.begin();
  do{
    if(it->second == a){
      m_mapping.erase(it);
      it = m_mapping.begin();
    }
    ++it;
  }while(it != m_mapping.end() );
  }

void Config::dropKey(const Key& k){
  auto it = m_mapping.begin();
  do{
    if(it->first == k){
      m_mapping.erase(it);
      std::cout<<"dropped key "<<k<<std::endl;
      it = m_mapping.begin();
    }
    ++it;
  }while(it != m_mapping.end() );
  for(it = m_mapping.begin(); it != m_mapping.end(); ++it){
    std::cout<<"key : "<<(char)('A'+it->first)<<" -> "<<(int)it->second<<std::endl;
  }
}

std::string Config::keyToString(const Key& k) const{
  std::string res = "";
  if(k >= 0 && k <= 25){
     return (res += (char)('A'+k));
  }
  if(k >= 26 && k <= 35){
    return res += "Num"+('0'+(k-26));
  }
  return "?";
}
