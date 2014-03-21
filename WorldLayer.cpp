#include "WorldLayer.h"
#include "common.h"
USING_NS_CC;
bool WorldLayer::init(){
  Layer::init();

  //touch event
  auto listener = EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);
  listener->onTouchBegan = std::bind(&WorldLayer::TouchesBegan,this,std::placeholders::_1,std::placeholders::_2);
  listener->onTouchEnded = std::bind(&WorldLayer::TouchesEnded,this,std::placeholders::_1,std::placeholders::_2);
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

  //contact event

  auto contactlistener = EventListenerPhysicsContact::create();
  contactlistener->onContactBegin = CC_CALLBACK_2(WorldLayer::ContactBegan,this);

  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactlistener,this);

  //background,can be enhance by textcache.
  
  background = Sprite::create("background.jpg");
  
  auto background_size = background->getContentSize();
  background->setAnchorPoint(Point(0,0));
  background->setPosition(0,0);
  
  addChild(background);
  //ground
  ground = Node::create();
  ground->setPosition(Point(GAME_WIDTH,GAME_HEIGHT*GROUND_RATIO));
  ground->setTag(888);
  auto groundbody = PhysicsBody::createBox(Size(GAME_WIDTH*2,1),PhysicsMaterial(100,0.0,1.0));
  groundbody->setCategoryBitmask(GROUND_CATA_MASK);
  groundbody->setContactTestBitmask(GROUND_CONTACT_MASK);
  //CCLOG("ground mask: %d,%d,%d",VALKYRIE_CATA_MASK,STATIC_OBJ_CATA_MASK,INTERACT_OBJ_CATA_MASK);
  groundbody->setCollisionBitmask(GROUND_COLLISION_MASK);
  groundbody->setDynamic(false);
  ground->setPhysicsBody(groundbody);
  addChild(ground);

  //world room
  auto room = Node::create();
  auto roombody = PhysicsBody::createEdgeBox(background_size);

  room->setPhysicsBody(roombody);

  room->setPosition(background_size.width/2,background_size.height/2);

  addChild(room);
  return true;
}


bool WorldLayer::TouchesBegan(cocos2d::Touch* touch,cocos2d::Event* event){
  
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
      userscene->onNodeTouchedBegan(ret,tp);
    }
    else{//world touch
      userscene->onWorldTouchedBegan(tp);
    }
  }
  return true;
}

void WorldLayer::TouchesEnded(cocos2d::Touch* touch, cocos2d::Event* event){
  if (m_cTouchNode != NULL){
    userscene->onNodeTouchedEnd(m_cTouchNode);
    m_cTouchNode=NULL;
  }
  else{
    userscene->onWorldTouchedEnd();
  }
}

bool WorldLayer::ContactBegan(cocos2d::EventCustom* event, const cocos2d::PhysicsContact& contact){
  //check our range shape
  PhysicsShape* range_shape;
  PhysicsShape* obj_shape;
  if (contact.getShapeA()->getTag() == 911){
    range_shape = contact.getShapeA();
    obj_shape = contact.getShapeB();
    CCLOG("tag of obj_shape %d",obj_shape->getBody()->getNode()->getTag());
  }
  else if(contact.getShapeB()->getTag() == 911){
    range_shape = contact.getShapeB();
    obj_shape = contact.getShapeA();
    CCLOG("119 contact");
  }
  else{
    
    return true;
  }
  CCLOG("contact here!!!!");
  userscene->onRangeContactBegan(range_shape->getBody()->getNode(),obj_shape->getBody()->getNode());
  //  userscene->on
  return true;
}

Size WorldLayer::getWorldSize(){//world size now equal to backgournd size
  CCLOG("background size %f ",background->getContentSize().width);
  return background->getContentSize();
}

void WorldLayer::update(float dt){

}

WorldLayer::WorldLayer():Layer(),userscene(NULL),background(NULL),m_cTouchNode(NULL){
  CCLOG("WorldLayer ctor called");
}

float WorldLayer::getGroundHeight(){
  return ground->getPosition().y;
}
  

