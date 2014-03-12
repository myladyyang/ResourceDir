#include "TestScene.h"

USING_NS_CC;
TestScene::TestScene():UserScene(){

  CCLOG("TestScene construct");
}


bool TestScene::init(){
  CCLOG("in Test Scene");
  UserScene::init();
  // auto touchlistener = EventListenerTouchOneByOne::create();

  // touchlistener->onTouchBegan = std::bind(&TestScene::TouchesBegan,this,std::placeholders::_1,std::placeholders::_2);
  // touchlistener->setSwallowTouches(true);
  // auto dispatcher = Director::getInstance()->getEventDispatcher();
     
  // dispatcher->addEventListenerWithSceneGraphPriority(touchlistener,this);

  //prepare layer and sprites here

  return true;
}


