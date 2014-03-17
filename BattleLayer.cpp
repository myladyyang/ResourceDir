#include "BattleLayer.h"
USING_NS_CC;


bool BattleLayer::init(){
  if( !LayerColor::initWithColor(Color4B::WHITE)){
    return false;
  }
  CCLOG("Battle init start");
  setAnchorPoint(Point(0,0));
  setPosition(Point(0,0));
  this->setContentSize(Size(84,28));
  b_act1 = Sprite::create("button1.jpg");
  b_act2 = Sprite::create("button1.jpg");
  b_act3 = Sprite::create("button1.jpg");
  b_act4 = Sprite::create("button1.jpg");

  b_act1->setPosition(14,14);
  b_act2->setPosition(42,14);
  b_act3->setPosition(80,14);
  b_act4->setPosition(108,14);
    
  
  b_act1->setScale(0.3);
  b_act2->setScale(0.3);
  b_act3->setScale(0.3);
  b_act4->setScale(0.3);

  // b_act1->setVisible(false);
  // b_act2->setVisible(false);
  // b_act3->setVisible(false);
  // b_act4->setVisible(false);
  
  this->addChild(b_act1,1);
  this->addChild(b_act2,1);
  this->addChild(b_act3,1);
  this->addChild(b_act4,1);



  return true;
}


void BattleLayer::FadeOut(){
  this->runAction(FadeOut::create(2.0f));
}
