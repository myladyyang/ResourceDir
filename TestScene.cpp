#include "TestScene.h"
#include "Valkyrie.h"
#include <unistd.h>
USING_NS_CC;
TestScene::TestScene():UserScene(){
  
  CCLOG("TestScene construct");
}

bool TestScene::SceneBuild(){
  auto player = Valkyrie::create("player");

  player->SetMoveAnimation("Animation1");
  player->SetJumpAnimation("Animation1");
  player->SetJump2Animation("Animation1");

  player->getPhysicsBody()->setCategoryBitmask(0x00000001);
  player->getPhysicsBody()->setContactTestBitmask(0x00000001);
  player->getPhysicsBody()->setCollisionBitmask(0x00000001);

  addPlayer(player);

  auto car = Sprite::create("boss.jpg");
  car->setScale(0.5);
  car->setContentSize(Size(217,233));



  auto carbody = PhysicsBody::createBox(Size(108.5,116.5),PhysicsMaterial(0,0,0.9));
  carbody->setCategoryBitmask(0x00000010);
  //  carbody->setContactTestBitmask(0x00000010);
  carbody->setCollisionBitmask(0x00000010);
  carbody->setRotationEnable(false);
  carbody->setDynamic(false);
  
  car->setPhysicsBody(carbody);
  car->setPosition(Point(GAME_WIDTH/2+200 ,getWorldLayer()->getGroundHeight() + 58.25));

  AddNodetoWorld(car,1);

  // //test pause
  // auto mo = Node::create();
  // mo->setContentSize(Size(50,50));
  // auto mobody = PhysicsBody::createBox(Size(50,50),PhysicsMaterial(0,0,0));
  // mobody->setCategoryBitmask(0x00000100);
  // mobody->setCollisionBitmask(0x00000100);
  // mobody->setVelocity(Vect(20,0));
  // mo->setPhysicsBody(mobody);
  // mo->setPosition(Point(25,getWorldLayer()->getGroundHeight()+25));
  
  // AddNodetoWorld(mo,2);
  

  return true;
}

bool TestScene::init(){
  UserScene::init();

  initCache("player.ExportJson");
  
  return true;
}


