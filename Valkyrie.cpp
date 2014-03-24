#include "Valkyrie.h"
#include "common.h"
USING_NS_CC;

const PhysicsMaterial common_material(0.0f,0.1f,0.3f);


Valkyrie::Valkyrie():Armature(){
  toward = true;
  weapon_value =0;
}

bool Valkyrie::getToward(){
  return toward;;
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

   body->setCategoryBitmask(VALKYRIE_CATA_MASK);
   body->setContactTestBitmask(VALKYRIE_CONTACT_MASK);
   body->setCollisionBitmask(0xFFFFFFFF);
  
  auto range = PhysicsShapeCircle::create(100);
  range->setCategoryBitmask(RANGE_CATA_MASK);
  range->setContactTestBitmask(RANGE_CONTACT_MASK);
  range->setCollisionBitmask(RANGE_COLLISION_MASK);
  range->setMass(0.1f);
  range->setTag(911);
  m_range = range;
  
  body->addShape(range);
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

void Valkyrie::Move(bool to){
  action_state=ActionState::MOVE;
  toward =to;
  getAnimation()->play("Animation1");
  if (to){
    this->getPhysicsBody()->setVelocity(Vect(VALKYRIE_SPEED,0));
  }
  else{
    this->getPhysicsBody()->setVelocity(Vect(-VALKYRIE_SPEED,0));
  }
    
}

void Valkyrie::Jump(bool to){
  if (weapon_value <2){
    weapon_value++;
  }
  else{
    battle_state = BattleState::MAXSATE;
  }
  bool doaction = false;
  switch(action_state){
  case ActionState::STANDBY:
    getAnimation()->play(animation_jump);
    action_state=ActionState::JUMP;
    doaction = true;
    break;
  case ActionState::JUMP2:
    getAnimation()->play(animation_jump2);
    doaction = true;
    break;
  case ActionState::MOVE:
    getAnimation()->play(animation_move);
    doaction = true;
    break;
  default:
    break;
  }

  if (!doaction){
    return;
  }

  toward = to;
  if(to){
    this->getPhysicsBody()->setVelocity(Vect(VALKYRIE_SPEED,VALKYRIE_JUMPHIGH));
  }
  else{
    this->getPhysicsBody()->setVelocity(Vect(-VALKYRIE_SPEED,VALKYRIE_JUMPHIGH));
  }
}


void Valkyrie::Jump2(bool toward){
  if (action_state == ActionState::JUMP){
    action_state = ActionState::JUMP2;
    Jump(toward);
  }
}

void Valkyrie::Stop(){
  this->getPhysicsBody()->setVelocity(Vect(0,0));
  action_state=ActionState::STANDBY;
}
bool Valkyrie::IsMoving(){
  return (getPhysicsBody()->getVelocity() != Point(0,0));
}


void Valkyrie::StopMoveAnimation(){
  getAnimation()->stop();
}

void Valkyrie::setBattleState(BattleState state){
  if (state == BattleState::NORMALSTATE){
    weapon_value = 0;
  }
  battle_state = state;
}
