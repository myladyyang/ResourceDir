#include "TestScene.h"
#include "Valkyrie.h"
USING_NS_CC;
TestScene::TestScene():UserScene(){
  
  CCLOG("TestScene construct");
}


bool TestScene::init(){
  CCLOG("in Test Scene");
  UserScene::init();

  
  initCache("player.ExportJson");
  auto player = Valkyrie::create("player");
  
  addPlayer(player);

  
  return true;
}


