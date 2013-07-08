#include <cstdio> //DELETE

#include "../headers/Action.hpp"

#include <sstream>
#include <string>
#include <vector>

//extern std::vector< Action::Framing_t > Framing_AttackL;
namespace Action{

  Subject getDoer(const action& a){
    int f = (1<<7);
    return (Subject)( (a&f) == 0?0:1 );
  }

  Subject getTarget(const action& a){
    int f= 1<<6;
    return (Subject)( (a&f) == 0?0:1 );
  }

  Type getType(const action& a){
    int f = 1 + (1<<1) + (1<<2) + (1<<3) + (1<<4) + (1<<5);
    return (Type) (a&f);
  }


  byte doerToByte(const Subject& d){
    return d<<7;
  }

  byte targetToByte(const Subject& t){
    return t<<6;
  }

  byte actionToByte(const Type& a, const Subject& doer, const Subject& target){
    return a+(doer<<7)+(target<<6);
  }


  std::string actionToString(const action& a){
    std::ostringstream oss;
    if(getDoer(a) == PLAYER1){
      oss << "Player1 - ";
    }else{
      oss << "Player2 - ";
    }
    oss << typeToString(getType(a) );
    return oss.str();
  }

  std::string typeToString(const Type& t){
    switch( t ){
    case NORMAL: return "Normal"; break;
    case ATTACK_LEFT: return "Attack Left"; break;
    case ATTACK_MIDDLE: return "Uppercut"; break;
    case ATTACK_RIGHT: return "Attack Right"; break;
    case DODGE_LEFT: return "Dodge Left"; break;
    case DODGE_MIDDLE: return "Dodge Middle"; break;
    case DODGE_RIGHT: return "Dodge Right"; break;
    case PAUSE: return "Pause"; break;
    default: return "Unknown"; break;
    }
    return "Unknown";
  }



  // Here begin all the framing stuff, for synchro of actions (and animations)

  std::vector< Framing_t > Framing_Normal = initFramingN();
  std::vector< Framing_t > Framing_AttackL = initFramingAL();
  std::vector< Framing_t > Framing_AttackM = initFramingAM();
  std::vector< Framing_t > Framing_AttackR = initFramingAR();
  std::vector< Framing_t > Framing_DodgeL = initFramingDL();
  std::vector< Framing_t > Framing_DodgeM = initFramingDM();
  std::vector< Framing_t > Framing_DodgeR = initFramingDR();
  std::vector< Framing_t > Framing_Stroke = initFramingStroke();

  std::vector<Framing_t> initFramingN(){ 
    Framing_t _0;
    Framing_t _1;
    Framing_t _2;
    Framing_t _3;
    _0.nb_frames = 1; //middle
    _1.nb_frames = 1; //left
    _2.nb_frames = 1; //middle
    _3.nb_frames = 1; //right
    std::vector<Framing_t> t;
    t.push_back(_0);
    t.push_back(_1);
    t.push_back(_2);
    t.push_back(_3);
    return t;
  }

  std::vector<Framing_t> initFramingAL(){
    Framing_t _0; 
    Framing_t _1;
    Framing_t _2;
    Framing_t _3;
    _0.nb_frames = 2; //preparing
    _1.nb_frames = 4; //striking
    _2.nb_frames = 2; //pausing
    _3.nb_frames = 1; //recovering
    std::vector<Framing_t> t;
    t.push_back(_0);
    t.push_back(_1);
    t.push_back(_2);
    t.push_back(_3);
    return t;
  }

  std::vector<Framing_t> initFramingAM(){
    Framing_t _0;
    Framing_t _1;
    Framing_t _2;
    Framing_t _3;
    _0.nb_frames = 3; //preparing
    _1.nb_frames = 3; //striking
    _2.nb_frames = 4; //pausing
    _3.nb_frames = 1; //recovering
    std::vector<Framing_t> t;
    t.push_back(_0);
    t.push_back(_1);
    t.push_back(_2);
    t.push_back(_3);
    return t;
  }

  std::vector<Framing_t> initFramingAR(){
    Framing_t _0;
    Framing_t _1;
    Framing_t _2;
    Framing_t _3;
    _0.nb_frames = 2; //preparing
    _1.nb_frames = 4; //striking
    _2.nb_frames = 2; //pausing
    _3.nb_frames = 1; //recovering
    std::vector<Framing_t> t;
    t.push_back(_0);
    t.push_back(_1);
    t.push_back(_2);
    t.push_back(_3);
    return t;
  }

  std::vector<Framing_t> initFramingDL(){ 
    Framing_t _0;
    Framing_t _1;
    Framing_t _2;
    _0.nb_frames = 1; //moving
    _1.nb_frames = 1; //pausing
    _2.nb_frames = 1; //recovering
    std::vector<Framing_t> t;
    t.push_back(_0);
    t.push_back(_1);
    t.push_back(_2);
    return t;
  }

  std::vector<Framing_t> initFramingDM(){
    Framing_t _0;
    Framing_t _1;
    Framing_t _2;
    _0.nb_frames = 1; //moving
    _1.nb_frames = 1; //pausing
    _2.nb_frames = 1; //recovering
    std::vector<Framing_t> t;
    t.push_back(_0);
    t.push_back(_1);
    t.push_back(_2);
    return t;
  }

  std::vector<Framing_t> initFramingDR(){
    Framing_t _0;
    Framing_t _1;
    Framing_t _2;
    _0.nb_frames = 1; //moving
    _1.nb_frames = 1; //pausing
    _2.nb_frames = 1; //recovering
    std::vector<Framing_t> t;
    t.push_back(_0);
    t.push_back(_1);
    t.push_back(_2);
    return t;
  }

  std::vector<Framing_t> initFramingStroke(){
    Framing_t _0;
    Framing_t _1;
    _0.nb_frames = 2; //crying
    _1.nb_frames = 1; //recovering
    std::vector<Framing_t> t;
    t.push_back(_0);
    t.push_back(_1);
    return t;
  }


}
