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
  player->SetMoveAnimation("Animation1");
  player->SetJumpAnimation("Animation1");
  player->SetJump2Animation("Animation1");

  player->getPhysicsBody()->setCategoryBitmask(0x00000001);
  player->getPhysicsBody()->setContactTestBitmask(0x00000001);
  player->getPhysicsBody()->setCollisionBitmask(0x00000001);

  addPlayer(player);

  auto car = Node::create();
  car->setContentSize(Size(100,100));
  auto carbody = PhysicsBody::createBox(Size(50,50),PhysicsMaterial(0,0,0.9));
  carbody->setCategoryBitmask(0x00000010);
  //  carbody->setContactTestBitmask(0x00000010);
  carbody->setCollisionBitmask(0x00000010);
  carbody->setRotationEnable(false);
  carbody->setDynamic(false);
  
  car->setPhysicsBody(carbody);
  car->setPosition(Point(GAME_WIDTH/2+200 ,getWorldLayer()->getGroundHeight()+150));

  AddNodetoWorld(car,1);
  
  return true;
}


