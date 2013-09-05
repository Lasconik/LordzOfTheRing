#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
namespace StateID{

  typedef enum{
    SPLASH,
    MAIN_MENU,
    OPTIONS_MENU,
    PROFILE_MENU,
    CHARACTER_MENU,
    MATCH,
    PAUSE
  } ID;
};

class GameState{

public:
  virtual void update() = 0;
  virtual void render() = 0;
  virtual bool enter() = 0;
  virtual bool exit() = 0;
  virtual std::string getID() const = 0;


};

#endif
