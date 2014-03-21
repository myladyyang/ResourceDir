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
  
  BattleState getBattleState(){return battle_state;}
  void setBattleState(BattleState state);
  
  cocos2d::PhysicsShape* getRange(){return m_range;}


  bool IsMoving();
  bool getToward();
  
  void SetMoveAnimation(std::string movestr){animation_move = movestr;}
  void SetJumpAnimation(std::string jumpstr){animation_jump = jumpstr;}
  void SetJump2Animation(std::string jump2str){animation_jump2 = jump2str;}

  //only move need to stop..
  void StopMoveAnimation();

protected:
  Valkyrie();
  
  float getXposition(){return getPosition().x;};
  
  BattleState battle_state;
  ActionState action_state;
  int weapon_value;//this value reach to 10, change to battle status
  bool toward;
  friend class UserScene;

private:
  std::string animation_move;
  std::string animation_jump;
  std::string animation_jump2;
  cocos2d::PhysicsShape* m_range;
};



#endif
