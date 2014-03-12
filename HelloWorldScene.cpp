#include "HelloWorldScene.h"

#include <stdlib.h>
#include "GamePlay.h"
#define COCOS2D_DEBUG 1
USING_NS_CC;


bool Gettest(Touch*,Event*){

  return true;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    scene->getPhysicsWorld()->setGravity(Vect(0,-100));
    scene->getPhysicsWorld()->setSpeed(3.0);
    layer->setPhyWorld(scene->getPhysicsWorld());
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


    const PhysicsMaterial hardma(0.0f,0.1f,0.3f);
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    screen = visibleSize;
    auto ground = Sprite::create("background.png");
    auto groundbody =PhysicsBody::createEdgeBox(Size(visibleSize.width,1),hardma,0);
    groundbody->setDynamic(false);
    ground->setPhysicsBody(groundbody);
    
    ground->setPosition(Point(origin.x + visibleSize.width/2,origin.y + visibleSize.height/9));

    background = Node::create();
    auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width,(visibleSize.height/4)*3),hardma,0);

    body->setDynamic(false);
    background->setPhysicsBody(body);
    background->setPosition(Point(origin.x + visibleSize.width/2,origin.y + visibleSize.height/2));
    this->addChild(ground);
    this->addChild(background);

    
    // auto edgenode = Node::create();
    // edgenode->setPosition(Point(visibleSize.width/2,(visibleSize.height/4 + (visibleSize.height/4)*3)/2));
    // //    edgenode->setPosition(Point(50,50));
    // edgenode->setPhysicsBody(body);
    // background->addChild(edgenode);


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

    auto playerbody = PhysicsBody::createBox(Size(player->getContentSize().width/10,player->getContentSize().height/10),hardma);
    playerbody->setMass(1000.0);
    playerbody->setRotationEnable(false);
    playerbody->setDynamic(true);

    player->setPhysicsBody(playerbody);

    player->setPosition(Point(origin.x + 100,origin.y + visibleSize.height/4));
    pp = player->getPosition();
    player->setScale(0.1);
    this->addChild(player,1);


    auto car = Node::create();
    auto carbody = PhysicsBody::createBox(Size(100,70),hardma);
    car->setContentSize(Size(50,50));
    carbody->setDynamic(false);
    carbody->setMass(20.0);
    car->setPhysicsBody(carbody);
    car->setPosition(Point(origin.x + visibleSize.width/3 *2 ,origin.y + visibleSize.height/4));

    background->addChild(car,1,1);
    

    locked = false;

    //phycisc

    auto contactlistener = EventListenerPhysicsContact::create();
    contactlistener->onContactBegin = CC_CALLBACK_2(HelloWorld::ContactBegan,this);
    //    contactlistener->onContactPreSolve = CC_CALLBACK_2(HelloWorld::ContactBegan,this);
    //touch
     auto touchlistener = EventListenerTouchOneByOne::create();
     touchlistener->onTouchEnded = std::bind(&HelloWorld::TouchesEnded,this,std::placeholders::_1,std::placeholders::_2);
     touchlistener->onTouchBegan = std::bind(&HelloWorld::TouchesBegan,this,std::placeholders::_1,std::placeholders::_2);
     
     touchlistener->setSwallowTouches(true);
     auto dispatcher = Director::getInstance()->getEventDispatcher();
     
     dispatcher->addEventListenerWithSceneGraphPriority(touchlistener,player);
     dispatcher->addEventListenerWithSceneGraphPriority(contactlistener,car);

     this->schedule(schedule_selector(HelloWorld::CameraUpdate));
     this->scheduleUpdate();
     inaction = false;
     return true;
}

void HelloWorld::CameraUpdate(float delta){
  
}
//50pix a step in one second
bool HelloWorld::ContactBegan(EventCustom* event, const PhysicsContact& contact){
  player->getPhysicsBody()->setVelocity(Vect(0,0));
  inaction = false;
  //hahah

  
  return true;
}

void HelloWorld::MoveStep(Point* src,Point* dest){

  kmVec2 vec,outvec;
  vec.x = dest->x - src->x;
  vec.y = dest->y - src->y;
  auto len = kmVec2Length(&vec);
  double ratio = 50/len;
  kmVec2Scale(&outvec,&vec,ratio);
  if (abs(vec.y/vec.x * 100) < 30){

    onestep.x = outvec.x;
    onestep.y = 0;

  }
  else{
    onestep.x = outvec.x;
    onestep.y = outvec.y;

  }

}

void HelloWorld::update(float dt){
  if (!inaction){
    return;
  }
  
  Point ppnew = player->getPhysicsBody()->getPosition();
  CCLOG("player location %f  - %f", ppnew.x,ppnew.y);
  Director::getInstance()->setModelView(-(ppnew.x -pp.x),-(ppnew.y-pp.y),0);
  pp = ppnew;
}

bool HelloWorld::TouchesBegan(Touch* touch,Event* event){
   // auto dstlocation = touch->getLocationInView();
   // dstlocation = Director::getInstance()->convertToGL(dstlocation);
   // auto srclocation = player->getPosition();
   // auto bklocation = background->getPosition();
  
  player->getPhysicsBody()->setVelocity(Vect(50,150));
  inaction = true;
  //  this->schedule(schedule_selector(HelloWorld::LongTouch),1);

  return true;
}
void HelloWorld::LongTouch(float dt){
  //  player->getPhysicsBody()->setVelocity(Vect(0,0));
  //  this->unschedule(schedule_selector(HelloWorld::LongTouch));

}
void HelloWorld::TouchesEnded(Touch* touch,Event* event){
  
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



