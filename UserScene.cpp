#include "UserScene.h"
#include "GamePlay.h"
#include "WorldLayer.h"
#include "Valkyrie.h"
USING_NS_CC;

void UserScene::end(){
  GamePlay::getInstance()->NextScene();
}

UserScene::UserScene():Scene(),player(NULL),worldlayer(NULL),syslayer(NULL){
  

}

UserScene::~UserScene(){

}

bool UserScene::init(){

  Scene::init();
  Scene::initWithPhysics();
  
  getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
  getPhysicsWorld()->setGravity(Vect(0,-100));
  getPhysicsWorld()->setSpeed(3.0);


  CCLOG("UserScene init entered");
  syslayer = SysLayer::create();
  worldlayer = WorldLayer::create();
  worldlayer->setUserScene(this);
  this->addChild(syslayer);
  this->addChild(worldlayer);

  WorldSize = worldlayer->getWorldSize();
  return true;
}


Scene * UserScene::create(){
  CCLOG("UserScene create");
  Scene *ret = new UserScene();
  if(ret && ret->init()){
    ret->autorelease();
    //we set the physical world property here


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

  if (player->getActionState() != ActionState::STANDBY){

    Point ppnew = player->getPhysicsBody()->getPosition();
    Director::getInstance()->setModelView(-(ppnew.x -pp.x),-(ppnew.y-pp.y),0);
    pp = ppnew;
  }
  //update camera..
}
#endif

void UserScene::addPlayer(Valkyrie * p){
  player = p;
  worldlayer->addChild(player);
  auto p_size = player->getContentSize();
  player->setPosition(Point(p_size.width/2*SCALE ,worldlayer->getGroundHeight()+p_size.height/2*SCALE));
}

void UserScene::setPlayerPostion(Point pos){
  player->setPosition(pos);
  pp = pos;
}

bool UserScene::initCache(const std::string json){
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo(json);
  return true;
}
