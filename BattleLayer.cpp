#include "BattleLayer.h"
USING_NS_CC;


bool BattleLayer::init(){
  if( !LayerColor::initWithColor(Color4B::BLACK)){
    return false;
  }
  clicknum = 0;
  setTag(99);
  CCLOG("Battle init start");
  
  setPosition(Point(-100,-100));

  this->setContentSize(Size(112,20));
  b_act1 = Sprite::create("button1.jpg");
  b_act2 = Sprite::create("button1.jpg");
  b_act3 = Sprite::create("button1.jpg");
  b_act4 = Sprite::create("button1.jpg");
  
  b_act1->setTag(1);
  b_act2->setTag(2);
  b_act3->setTag(3);
  b_act4->setTag(4);
  b_act1->setPosition(14,14);
  b_act2->setPosition(42,14);
  b_act3->setPosition(70,14);
  b_act4->setPosition(98,14);
    
  
  b_act1->setScale(0.3);
  b_act2->setScale(0.3);
  b_act3->setScale(0.3);
  b_act4->setScale(0.3);

  // b_act1->setVisible(false);
  // b_act2->setVisible(false);
  // b_act3->setVisible(false);
  // b_act4->setVisible(false);
  
  this->addChild(b_act1,11);
  this->addChild(b_act2,11);
  this->addChild(b_act3,11);
  this->addChild(b_act4,11);
  
  // auto listener = EventListenerTouchOneByOne::create();
  // listener->setSwallowTouches(true);
  // listener->onTouchBegan = std::bind(&BattleLayer::TouchesBegan,this,std::placeholders::_1,std::placeholders::_2);

  return true;
}

BT_NUM BattleLayer::ButtonClick(Point tp){
  if (tp.x >0 && tp.x < 28){
    b_act1->setTexture("button2.jpg");
  }
  CCLOG("button click");
  return BT_NUM::Button_A;
}

void BattleLayer::FadeOut(){
  this->runAction(FadeOut::create(1.0f));
  b_act1->runAction(FadeOut::create(1.0f));
  b_act2->runAction(FadeOut::create(1.0f));
  b_act3->runAction(FadeOut::create(1.0f));
  b_act4->runAction(FadeOut::create(1.0f));
}

void BattleLayer::FadeIn(){
  this->runAction(FadeIn::create(1.0f));
  b_act1->runAction(FadeIn::create(1.0f));
  b_act2->runAction(FadeIn::create(1.0f));
  b_act3->runAction(FadeIn::create(1.0f));
  b_act4->runAction(FadeIn::create(1.0f));
}
