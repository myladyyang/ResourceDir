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
    
    screen = visibleSize;
    background = Sprite::create("background.png");

    auto backgroundsize = background->getContentSize();
    
    background->setPosition(Point(origin.x + backgroundsize.width/2,origin.y + backgroundsize.height/2));

    this->addChild(background,0);
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
    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("player.ExportJson");
    player = cocostudio::Armature::create("player");

    
    player->setPosition(Point(origin.x + visibleSize.width/2,origin.y + visibleSize.height/4));
    player->setScale(0.1);
    this->addChild(player,1);


    inaction = false;
    locked = false;

    

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
    //    CCLOG("ratio of vec.y/vec.x = %d",abs(vec.y/vec.x * 100));
    onestep.x = outvec.x;
    onestep.y = 0;
    //    CCLOG("OUTSTEP : %f --- %f",onestep.x,onestep.y);
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
  auto bklocation = background->getPosition();
  MoveStep(&srclocation,&dstlocation);

  // design for camera thing...
  
  auto limitleft = (bklocation.x - background->getContentSize().width/2 +50 >=0 );
  auto limitright = (background->getContentSize().width/2 + bklocation.x <= screen.width + 50);
  CCLOG("bklocation %f, bkwidth %f, screenwidth %f",bklocation.x,background->getContentSize().width/2,screen.width);
  auto limit = true;
  CCLOG("limitright %d,  limitleft %d, toward: %f, location : %d",limitright,limitleft,onestep.x,abs(srclocation.x-screen.width/2));
  if((limitright && (onestep.x > 0)) || (limitleft && (onestep.x <0))){
      CCLOG("player move");
      CCLOG("toword: %f", onestep.x);
      limit = true;
    }
  if(((limitright && (onestep.x <0)) || (limitleft && (onestep.x >0))) && (abs(srclocation.x - screen.width/2) <50)){
    CCLOG("reach middle and direct change");
    limit = false;
  }
  if(!limitright && !limitleft){
    limit = false;
  }
  int jumpheight = -50;
  Node* moveable;
  if(limit ){
    moveable = dynamic_cast<Node*>(player);
    bklocation = srclocation;
    jumpheight = 50;

    CCLOG("breaking limit");
  }
  else{
    moveable = dynamic_cast<Node*>(background);
    onestep.x = -onestep.x;
  }
 
  
  this->schedule(schedule_selector(HelloWorld::LongTouch),0.2);
  if(limit && (srclocation.x +50 > screen.width && (onestep.x - srclocation.x) > 0)){

    CCLOG("right end,stoping");
    return true;
  }
  if(limit && ((srclocation.x -100) <0 && onestep.x < 0)){
    CCLOG("left end,stoping, move x %f", srclocation.x);

    return true;
  }
  
  if(onestep.y ==0){
    player->getAnimation()->play("Animation1");

      moveable->runAction(CCSequence::create(CallFunc::create(std::bind(&HelloWorld::ActionStart,this)),MoveTo::create(0.2,Point(bklocation.x + onestep.x,bklocation.y)),CallFunc::create(std::bind(&HelloWorld::ActionClean,this)),NULL));


  }
  else{
    player->getAnimation()->play("Animation1");
    moveable->runAction(CCSequence::create(CallFunc::create(std::bind(&HelloWorld::ActionStart,this)),JumpTo::create(0.5,Point(bklocation.x + onestep.x,bklocation.y),jumpheight,1),CallFunc::create(std::bind(&HelloWorld::ActionClean,this)),NULL));

  }
  
  return true;
}
void HelloWorld::LongTouch(float dt){

  auto srclocation = player->getPosition();
  auto bklocation = background->getPosition();
  // design for camera thing...
  auto limitleft = (bklocation.x - background->getContentSize().width/2 +50 >=0 );
  auto limitright = (bklocation.x + background->getContentSize().width/2 <= screen.width + 50);

  CCLOG("bklocation %f, bkwidth %f, screenwidth %f",bklocation.x,background->getContentSize().width/2,screen.width);
  auto limit = true;
  CCLOG("limitright %d,  limitleft %d, toward: %f, location : %d",limitright,limitleft,onestep.x,abs(srclocation.x-screen.width/2));
  if((limitright && (onestep.x > 0)) || (limitleft && (onestep.x <0))){
      CCLOG("player move");
      CCLOG("toword: %f", onestep.x);
      limit = true;
    }
  if(((limitright && (onestep.x <0)) || (limitleft && (onestep.x >0))) && (abs(srclocation.x - screen.width/2) <50)){
    CCLOG("reach middle and direct change");
    limit = false;
  }
  if(!limitright && !limitleft){
    limit = false;
  }
  int jumpheight = -50;
  Node* moveable;
  double movex = onestep.x;
  if(limit ){
    moveable = dynamic_cast<Node*>(player);
    bklocation = srclocation;
    jumpheight = 50;

    CCLOG("breaking limit");
  }
  else{
    moveable = dynamic_cast<Node*>(background);
    movex = -onestep.x;
  }
 
  
  if(limit && (srclocation.x +50 > screen.width && (onestep.x > 0))){

    CCLOG("right end,stoping");
    return ;
  }
  if(limit && ((srclocation.x -100) <0 && onestep.x < 0)){
    CCLOG("left end,stoping, move x %f", srclocation.x);

    return;
  }

  
  if (onestep.y ==0){
    player->getAnimation()->play("Animation1");
    moveable->runAction(MoveTo::create(0.2,Point(bklocation.x + movex,bklocation.y)));

  }
  else{
      if (inaction == true){
	return;
      }
      player->getAnimation()->play("Animation1");
      moveable->runAction(CCSequence::create(CallFunc::create(std::bind(&HelloWorld::ActionStart,this)),JumpTo::create(0.5,Point(bklocation.x + movex,bklocation.y),jumpheight,1),CallFunc::create(std::bind(&HelloWorld::ActionClean,this)),NULL));

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
