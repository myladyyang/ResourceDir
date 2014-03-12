#include "UserScene.h"
#include "GamePlay.h"
#include "WorldLayer.h"
USING_NS_CC;
void UserScene::end(){
  GamePlay::getInstance()->NextScene();
}

UserScene::UserScene():Scene(),player(NULL),worldlayer(NULL),syslayer(NULL){

  CCLOG("UserScene construct");
}

UserScene::~UserScene(){

}

bool UserScene::init(){
  Scene::init();
  CCLOG("UserScene init entered");
  syslayer = SysLayer::create();
  worldlayer = WorldLayer::create();
  worldlayer->setUserScene(this);
  this->addChild(syslayer);
  this->addChild(worldlayer);

  return true;
}


Scene * UserScene::createWithPhysics(){
  Scene *ret = new UserScene();
  if(ret && ret->initWithPhysics()){
    ret->autorelease();
    //we set the physical world property here
    ret->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    ret->getPhysicsWorld()->setGravity(Vect(0,-100));
    ret->getPhysicsWorld()->setSpeed(3.0);
    ret->init();
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

  if (player != NULL){

    Point ppnew = player->getPhysicsBody()->getPosition();
    Director::getInstance()->setModelView(-(ppnew.x -pp.x),-(ppnew.y-pp.y),0);
    pp = ppnew;
  }
  //update camera..
}
#endif
//player move code should be added here or some more complicate code
//void UserScene::onNodeTouchedBegan(Node* node,Point tp){
  //play animation on node...
  //@code
  //node->touched() or something else...
  
  

//}
