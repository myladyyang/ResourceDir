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

  auto car = Node::create();
  auto carbody = PhysicsBody::createBox(Size(50,50),PhysicsMaterial(0,0,0.9));
  carbody->setRotationEnable(false);
  carbody->setDynamic(false);
  
  car->setPhysicsBody(carbody);
  car->setPosition(Point(GAME_WIDTH/2+200 ,getWorldLayer()->getGroundHeight()+25));

  AddNodetoWorld(car,1);
  
  return true;
}


