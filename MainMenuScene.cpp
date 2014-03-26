#include "MainMenuScene.h"
#include "common.h"
#include "GamePlay.h"
USING_NS_CC;

bool MainMenuScene::init(){
  Scene::init();
  
  auto layer = Layer::create();
  layer->setAnchorPoint(Point(0,0));
  layer->setContentSize(Size(GAME_WIDTH,GAME_HEIGHT));
  layer->setPosition(0,0);
  addChild(layer);

  auto background = Sprite::create("menubackground.jpg");
  background->setAnchorPoint(Point(0,0));
  background->setPosition(Point(0,0));

  auto menu_1 = MenuItemImage::create("enter.png","enter.png",CC_CALLBACK_1(MainMenuScene::EnterGameCallback,this));
  

  auto menu = Menu::create(menu_1,NULL);
  menu->setPosition(Point(GAME_WIDTH/2,GAME_HEIGHT/2));
  
  layer->addChild(background);
  layer->addChild(menu);

  return true;
}

void MainMenuScene::end(){
  CCLOG("main scene left");
  GamePlay::getInstance()->NextScene();
}

void MainMenuScene::EnterGameCallback(Object* pSender){
  
  end();
}
 void MainMenuScene::load(){}
