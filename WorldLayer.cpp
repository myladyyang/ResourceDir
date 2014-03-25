#include "WorldLayer.h"
#include "common.h"
USING_NS_CC;
bool WorldLayer::init(){
  Layer::init();
  setTag(108);
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
  background->setTag(106);
  addChild(background);
  //ground
  ground = Node::create();
  ground->setPosition(Point(background_size.width/2,GAME_HEIGHT*GROUND_RATIO));
  ground->setTag(888);
  auto groundbody = PhysicsBody::createBox(Size(background_size.width,1),PhysicsMaterial(100,0.0,1.0));

  groundbody->setCategoryBitmask(GROUND_CATA_MASK);
  groundbody->setContactTestBitmask(GROUND_CONTACT_MASK);

  groundbody->setCollisionBitmask(GROUND_COLLISION_MASK);
  groundbody->setDynamic(false);
  ground->setPhysicsBody(groundbody);
  addChild(ground);

  //world room
  auto room = Node::create();
  auto roombody = PhysicsBody::createEdgeBox(background_size);
  roombody->setCategoryBitmask(ROOM_CATA_MASK);
  roombody->setContactTestBitmask(NONE_MASK);
  roombody->setCollisionBitmask(ANY_MASK);
  room->setPhysicsBody(roombody);

  room->setPosition(background_size.width/2,background_size.height/2);

  addChild(room);
  return true;
}


bool WorldLayer::TouchesBegan(cocos2d::Touch* touch,cocos2d::Event* event){
  
  auto tp =  touch->getLocationInView();
  tp = Director::getInstance()->convertToGL(tp);
  tp = convertToNodeSpace(tp);
  int max_zorder = -2;
  Node* ret = NULL;
  for (const auto &child:_children){


    auto box = child->getBoundingBox();
    if (child->getTag() == BATTLE_TAG){
      CCLOG("click on point %f, %f",tp.x,tp.y);
      CCLOG("box of 99 is : %f,%f,%f,%f",box.size.width,box.size.height,box.origin.x,box.origin.y);
      CCLOG("battle layer content size: %f %f",child->getContentSize().width,child->getContentSize().height);
    }
    if(child->getBoundingBox().containsPoint(tp)){
      if (child->getTag() == 106){
	continue;
      }
      CCLOG("touch obj's tag is : %d",child->getTag());
      CCLOG("max zorder is : %d",max_zorder);
      if (child->getZOrder() > max_zorder){
	max_zorder=child->getZOrder();
	CCLOG("Change order");
	ret = child;
      }
    }
  }
  if(userscene != NULL){
    if(ret != NULL){//node touch
      m_cTouchNode = ret;
      CCLOG("node touch");
      userscene->onNodeTouchedBegan(ret,tp);
    }
    else{//world touch
      CCLOG("world touch");
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
    CCLOG("tag of object range %d",range_shape->getTag());
    CCLOG("CONTACT mask1 %d %d  ",range_shape->getContactTestBitmask(), obj_shape->getContactTestBitmask());
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
  

