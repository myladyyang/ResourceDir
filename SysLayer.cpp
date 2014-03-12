#include "SysLayer.h"
#include "GamePlay.h"
USING_NS_CC;
bool SysLayer::init(){
  CCLOG("syslayer init called");
  Layer::init();
  auto listener = EventListenerKeyboard::create();
  listener->onKeyPressed = CC_CALLBACK_2(SysLayer::onKeyPressed,this);
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
  return true;
}


SysLayer::SysLayer():Layer(){

}

void SysLayer::onKeyPressed(EventKeyboard::KeyCode keycode,Event* event){
  if (keycode == EventKeyboard::KeyCode::KEY_MENU || keycode == EventKeyboard::KeyCode::KEY_1){
    CCLOG("key f1 pressed");
    GamePlay::getInstance()->end();
  }
}
