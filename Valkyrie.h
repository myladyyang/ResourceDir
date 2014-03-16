#ifndef __VALKYRIE_H__
#define __VALKYRIE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

const float VALKYRIE_SPEED = 50;
const float VALKYRIE_JUMPHIGH = 150;
const float SCALE = 0.1;

enum class BattleState{
  MAXSATE,
  NORMALSTATE
    };

enum class ActionState{
  MOVE,
  JUMP,
  JUMP2,
  STANDBY,
  
    };
class Valkyrie: public cocostudio::Armature{
 public:
  //actions
  void Move(bool toward);//toward >0, right, toward < 0 left
  void Jump(bool toward);
  void Jump2(bool toward);
  void Stop();
  virtual bool init(const std::string& name);
  static  Valkyrie* create(const std::string& name);

  ActionState getActionState(){return action_state;}
  void setActionState(ActionState state){action_state = state;}
  bool IsMoving();
  bool getToward();

 protected:
  Valkyrie();
  
  float getXposition(){return getPosition().x;};
  
  BattleState battle_state;
  ActionState action_state;
  bool toward;
  friend class UserScene;
  
};



#endif
