#include "HelloWorldScene.h"
#include <stdlib.h>
#define COCOS2D_DEBUG 1
USING_NS_CC;


bool Gettest(Touch*,Event*){

  return true;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
  if ( !CCLayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    inaction = false;
    player = Sprite::create("Player.png");
    auto size = player->getContentSize().width;
    player->setPosition(Point( origin.x + size/2,  visibleSize.height/2+ origin.y));
    

    this->addChild(player,0);
    

    //touch
     auto touchlistener = EventListenerTouchOneByOne::create();
     touchlistener->onTouchEnded = std::bind(&HelloWorld::TouchesEnded,this,std::placeholders::_1,std::placeholders::_2);
     touchlistener->onTouchBegan = std::bind(&HelloWorld::TouchesBegan,this,std::placeholders::_1,std::placeholders::_2);

     touchlistener->setSwallowTouches(true);
     auto dispatcher = Director::getInstance()->getEventDispatcher();
     dispatcher->addEventListenerWithSceneGraphPriority(touchlistener,player);

    
     return true;
}
//50pix a step in one second
void HelloWorld::MoveStep(Point* src,Point* dest){
  kmVec2 vec,outvec;
  vec.x = dest->x - src->x;
  vec.y = dest->y - src->y;
  auto len = kmVec2Length(&vec);
  double ratio = 50/len;
  kmVec2Scale(&outvec,&vec,ratio);
  if (abs(vec.y/vec.x * 100) < 30){
    CCLOG("ratio of vec.y/vec.x = %d",abs(vec.y/vec.x * 100));
    onestep.x = outvec.x;
    onestep.y = 0;
    
  }
  else{
    onestep.x = outvec.x;
    onestep.y = outvec.y;

  }

}
void HelloWorld::ActionClean(){
  inaction = false;
}
void HelloWorld::ActionStart(){
  inaction = true;
}
bool HelloWorld::TouchesBegan(Touch* touch,Event* event){
  if (inaction == true){
    return true;
  }
  auto dstlocation = touch->getLocationInView();
  dstlocation = Director::getInstance()->convertToGL(dstlocation);
  auto srclocation = player->getPosition();
  
  MoveStep(&srclocation,&dstlocation);
  this->schedule(schedule_selector(HelloWorld::LongTouch),0.2);
  if(onestep.y ==0){
    player->runAction(CCSequence::create(CallFunc::create(std::bind(&HelloWorld::ActionStart,this)),MoveTo::create(0.2,Point(srclocation.x + onestep.x,srclocation.y)),CallFunc::create(std::bind(&HelloWorld::ActionClean,this)),NULL));
  }
  else{
    player->runAction(CCSequence::create(CallFunc::create(std::bind(&HelloWorld::ActionStart,this)),JumpTo::create(0.5,Point(srclocation.x + onestep.x,srclocation.y),50,1),CallFunc::create(std::bind(&HelloWorld::ActionClean,this)),NULL));
  }
  
  return true;
}
void HelloWorld::LongTouch(float dt){

  auto location = player->getPosition();
  if (onestep.y ==0){
    player->runAction(CCSequence::create(CallFunc::create(std::bind(&HelloWorld::ActionStart,this)),MoveTo::create(0.2,Point(location.x + onestep.x,location.y)),CallFunc::create(std::bind(&HelloWorld::ActionClean,this)),NULL));
  }
  else{
      if (inaction == true){
	return;
      }
    player->runAction(CCSequence::create(CallFunc::create(std::bind(&HelloWorld::ActionStart,this)),JumpTo::create(0.5,Point(location.x + onestep.x,location.y),50,1),CallFunc::create(std::bind(&HelloWorld::ActionClean,this)),NULL));
  }
  

}
void HelloWorld::TouchesEnded(Touch* touch,Event* event){
  this->unschedule(schedule_selector(HelloWorld::LongTouch));
}




void HelloWorld::spriteMoveFinished(Node* sender){
  this->removeChild(sender,true);

}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
