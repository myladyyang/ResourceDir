#include "WorldLayer.h"
#include "common.h"
USING_NS_CC;
bool WorldLayer::init(){
  Layer::init();
  auto listener = EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);
  listener->onTouchBegan = std::bind(&WorldLayer::TouchesBegan,this,std::placeholders::_1,std::placeholders::_2);
  listener->onTouchEnded = std::bind(&WorldLayer::TouchesEnded,this,std::placeholders::_1,std::placeholders::_2);
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

  //ground
  ground = Node::create();
  ground->setPosition(Point(GAME_WIDTH,GAME_HEIGHT*GROUND_RATIO));

  auto groundbody = PhysicsBody::createEdgeBox(Size(GAME_WIDTH*2,1));
  groundbody->setDynamic(false);
  ground->setPhysicsBody(groundbody);
  addChild(ground);

  
  return true;
}


bool WorldLayer::TouchesBegan(cocos2d::Touch* touch,cocos2d::Event* event){
  CCLOG("worldlayer touch");
  
  auto tp =  touch->getLocationInView();
  tp = Director::getInstance()->convertToGL(tp);
  int max_zorder = 0;
  Node* ret = NULL;
  for (const auto &child:_children){
    if(child->getBoundingBox().containsPoint(tp)){
      if (child->getZOrder() > max_zorder) ret = child;
    }
  }
  if(userscene != NULL){
    if(ret != NULL){//node touch
      m_cTouchNode = ret;
      userscene->onNodeTouchedBegan(ret);
    }
    else{//world touch
      userscene->onWorldTouchedBegan(tp);
    }
  }
  return true;
}

void WorldLayer::TouchesEnded(cocos2d::Touch* touch, cocos2d::Event* event){
  auto tp =  touch->getLocationInView();
  tp = Director::getInstance()->convertToGL(tp);
  if (m_cTouchNode != NULL){
    userscene->onNodeTouchedEnd(m_cTouchNode);
    m_cTouchNode=NULL;
  }
  else{
    userscene->onWorldTouchedEnd(tp);
  }
}

bool WorldLayer::ContactBegan(cocos2d::EventCustom* event, const cocos2d::PhysicsContact& contact){
  return true;
}

Size WorldLayer::getWorldSize(){//world size now equal to backgournd size
  return Size(GAME_WIDTH*2,GAME_HEIGHT*2);
}

void WorldLayer::update(float dt){

}

WorldLayer::WorldLayer():Layer(),userscene(NULL),background(NULL),m_cTouchNode(NULL){
  CCLOG("WorldLayer ctor called");
}

float WorldLayer::getGroundHeight(){
  return ground->getPosition().y;
}
  
