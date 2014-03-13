#include "Valkyrie.h"

USING_NS_CC;

const PhysicsMaterial common_material(0.0f,0.1f,0.3f);


Valkyrie::Valkyrie():Armature(){
  
}

bool Valkyrie::init(const std::string& name){
  if (!Armature::init(name)){
    return false;
  }
  CCLOG("Valkyrie init");
  battle_state = BattleState::NORMALSTATE;
  action_state = ActionState::STANDBY;

  //phy
  auto body = PhysicsBody::createBox(Size(getContentSize().width * SCALE,getContentSize().height * SCALE),common_material);
  body->setRotationEnable(false);
  body->setDynamic(true);
  setPhysicsBody(body);
  
  setScale(SCALE);
  return true;
}

Valkyrie *Valkyrie::create(const std::string& name)
{
    Valkyrie *val = new Valkyrie();
    if (val && val->init(name))
    {

        val->autorelease();
        return val;
    }
    CC_SAFE_DELETE(val);
    return nullptr;
}

void Valkyrie::Move(bool toward){
  action_state=ActionState::MOVE;
  if (toward > 0){
    this->getPhysicsBody()->setVelocity(Vect(VALKYRIE_SPEED,0));
  }
  else{
    this->getPhysicsBody()->setVelocity(Vect(-VALKYRIE_SPEED,0));
  }
    
}

void Valkyrie::Jump(bool toward){
  if (action_state != ActionState::STANDBY){//jump start form standby
    return;
  }
  action_state=ActionState::JUMP;
  if( toward >0){
    this->getPhysicsBody()->setVelocity(Vect(VALKYRIE_SPEED,VALKYRIE_JUMPHIGH));
  }
  else{
    this->getPhysicsBody()->setVelocity(Vect(-VALKYRIE_SPEED,VALKYRIE_JUMPHIGH));
  }
}


void Valkyrie::Jump2(bool toward){
  if (action_state == ActionState::JUMP){
    
    Jump(toward);
  }
}

void Valkyrie::Stop(){
  this->getPhysicsBody()->setVelocity(Vect(0,0));
  action_state=ActionState::STANDBY;
}
