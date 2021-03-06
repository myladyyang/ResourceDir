#include "UserScene.h"
#include "GamePlay.h"
#include "WorldLayer.h"
#include "Valkyrie.h"
#include <stdlib.h>
USING_NS_CC;


void UserScene::end(){
  GamePlay::getInstance()->NextScene();
}

UserScene::UserScene():Scene(),player(NULL),worldlayer(NULL),syslayer(NULL),battlelayer(NULL),m_scale(false),m_scale_thr(1.0),nodef(nullptr){
  ScreenSize = Size(GAME_WIDTH,GAME_HEIGHT);
  b_init = false;
  m_percent = 0;
  xupdate = true;
  yupdate = true;
  //strange after pause the player positon still have one frame change, I guess the physic check pause after node check..., that's why I add this flag to force stop node update.
  b_follow = false;
}

UserScene::~UserScene(){

}

bool UserScene::SceneBuild(){
  return true;
}

bool UserScene::init(){

  Scene::init();
  Scene::initWithPhysics();
  

  

  //  max_slider = ControlSlider::create

  return true;
}

void UserScene::load(){
  CCLOG("User Scene load");
  getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
  getPhysicsWorld()->setGravity(Vect(0,-100));
  getPhysicsWorld()->setSpeed(3.0);


  syslayer = SysLayer::create();
  worldlayer = WorldLayer::create();
  worldlayer->setUserScene(this);

  battlelayer = BattleLayer::create();

  worldlayer->addChild(battlelayer,10);
  this->addChild(syslayer);
  this->addChild(worldlayer);

  WorldSize = worldlayer->getWorldSize();
}

Scene * UserScene::create(){
  CCLOG("UserScene create");
  Scene *ret = new UserScene();
  if(ret && ret->init()){
    ret->autorelease();

    return ret;
  }
  else{
    CC_SAFE_DELETE(ret);
    return nullptr;
  }

}


WorldLayer* UserScene::getWorldLayer(){
  return worldlayer;
}


void UserScene::AddNodetoWorld(Node* snode,int zorder){
  worldlayer->addChild(snode,zorder);
}
#if CC_USE_PHYSICS
void UserScene::update(float delta){

  Node::update(delta);
  if (nullptr != _physicsWorld)
    {
      _physicsWorld->update(delta);
    }
  
  player->updatePhysicsTransform();
  

  if(!b_init){
    return;
  }
  auto ppnew = player->getPosition();
  auto pp2 = ppnew;
  //perforance enhanced here
  if (player->getXposition() <= ScreenSize.width/2+player->getContentSize().width/20 || player->getXposition() >= WorldSize.width-ScreenSize.width/2){
    if (xupdate == true){
      xupdate = false;
    }
    else{
      ppnew.x = pp.x;
    }
  }
  else{
    xupdate = true;
  }
  if (player->getActionState() != ActionState::STANDBY){
     Director::getInstance()->setModelView(-(ppnew.x -pp.x),-(ppnew.y-pp.y),0);
  }
   pp = pp2;
   //  scale here
   if(m_scale  ){
     battlescale();
   }
   //follow here
   if (b_follow){
     GamePlay::getInstance()->FollowNode(nodef);
     b_follow = false;
   }
}
#endif

void UserScene::battlescale(){
  if (m_scale_thr <= SCALE_THR){
    m_scale_thr += 0.01;
    setScale(m_scale_thr);
  }
}

void UserScene::unbattlescale(){

  m_scale_thr = 1.0;
  m_scale= false;
  setScale(1.0);
}


void UserScene::addPlayer(Valkyrie * p){
  player = p;
  worldlayer->addChild(player,10);
  auto p_size = player->getContentSize();
  player->setPosition(Point(p_size.width/2*SCALE + GAME_WIDTH/2 ,worldlayer->getGroundHeight()+p_size.height/2*SCALE));
  pp = player->getPosition();
  xupdate = pp.x > ScreenSize.width/2+player->getContentSize().width/20 ||pp.x < WorldSize.width-ScreenSize.width/2;
  
  
}

void UserScene::scheduleMove(float dt){
  auto toward = player->getToward();
  player->Move(toward);
}

void UserScene::initProgress(float percent){
  CCLOG("in progress : %f",percent);
  if(    percent == 1.0){
    CCLOG("Scene build called");
    b_init = SceneBuild();
  }
  m_percent = percent;


}

bool UserScene::initCache(const std::string json){

  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(json,this,schedule_selector(UserScene::initProgress));
  return true;
}

void UserScene::onNodeTouchedBegan(Node* node,Point tp){
  if(node ==NULL){
    CCLOG("NULL node touched");
  }
  auto tag = node->getTag();
  CCLOG("touch at node: %d",tag);
  if (tag == 99){
    auto basic = node->getPosition();
    onButtonClick(dynamic_cast<BattleLayer*>( node)->ButtonClick(Point(tp.x-basic.x,tp.y-basic.y)));
    getPhysicsWorld()->setSpeed(3.0f);
    player->setBattleState(BattleState::NORMALSTATE);
    unbattlescale();
    GamePlay::getInstance()->unFollow();
  }

}

void UserScene::onNodeTouchedEnd(Node* node){
  // battlelayer->FadeOut();
  // battlelayer->setPosition(Point(-100,-100));
  // CCLOG("touch node end , remove the battle layer");

}

void UserScene::onWorldTouchedBegan(Point tp){
  //  CCLOG("on world touch began,player at %f, %f",player->getPosition().x, player->getPosition().y);
  //  CCLOG("on world touch began,player at %f, %f",player->getPhysicsBody()->getPosition().x, player->getPhysicsBody()->getPosition().y);
  if(!player->IsMoving()){
    player->setActionState(ActionState::STANDBY);
  }

  Point delta;
  delta.x = tp.x - pp.x;
  delta.y = tp.y - pp.y;
  bool b_jump = false;

  if (delta.y >0){
    b_jump = delta.y/(abs(delta.x)*100)<40?true:false;
  }

  switch (player->getActionState()){
  case ActionState::STANDBY:
    if (!b_jump){
      //      CCLOG("player move");

      player->Move(delta.x>0?true:false);
      schedule(schedule_selector(UserScene::scheduleMove),0.2);
      break;
    }
    else{
      
      player->Jump(delta.x>0?true:false);
      break;
    }
  case ActionState::JUMP:
    CCLOG("jump2");

    player->Jump2(delta.x>0?true:false);
    break;
  case ActionState::MOVE:

    if (!b_jump){
	
      player->Move(delta.x>0?true:false);
      schedule(schedule_selector(UserScene::scheduleMove),0.2);
      break;
    }
    else{
      CCLOG("move,jump");
      player->Jump(delta.x>0?true:false);
      break;
    }
  default:
    break;
  }
}

void UserScene::onWorldTouchedEnd(){
  unschedule(schedule_selector(UserScene::scheduleMove));
  player->StopMoveAnimation();
}

void UserScene::onButtonClick(BT_NUM bn){
  switch(bn){
  case BT_NUM::Button_A:
    CCLOG("btn A clict");
    break;
  case BT_NUM::Button_B:
    break;
  case BT_NUM::Button_C:
    break;
  case BT_NUM::Button_D:
    break;
  }
}


void UserScene::onRangeContactBegan(Node* nodeA,Node* inter_obj){
  if (player->getBattleState() == BattleState::MAXSATE){
    battlelayer->FadeIn();
    auto pos = inter_obj->getPosition();
    pos = Point(pos.x,pos.y);
    battlelayer->setPosition(pos);
    getPhysicsWorld()->setSpeed(0);
    b_follow = true;
    m_scale = true;
    nodef = inter_obj;
    //GamePlay::getInstance()->FollowNode(inter_obj);
  }
  else{
    return;
  }
}

