#ifndef ACTION_HPP
#define ACTION_HPP

#include "../headers/Misc.hpp"

typedef byte action;
/** An action can be described in one byte:
 ABCDEFGH with
A = 0-1 for action's maker
B= 0-1 for action's target (optionnal)
CDEFGH = 000000-111111 for action term (up to 64 actions) 
*/

namespace NAction{
  typedef enum{
    UNKNOWN = 0,
    ATTACK_LEFT = 1,
    ATTACK_MIDDLE,
    ATTACK_RIGHT,
    DODGE_LEFT,
    DODGE_MIDDLE,
    DODGE_RIGHT,
    KO,
    SUPER_STRIKE,
    ACTIONS_COUNT
  } Action;
  
  typedef enum{
    PLAYER1 = 0,
    PLAYER2
  } Subject;

}

NAction::Action getAction(const action&);

NAction::Subject getTarget(const action&);

NAction::Subject getDoer(const action&);

#endif
