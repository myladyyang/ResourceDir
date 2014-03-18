#include "GamePlay.h"
#include "HelloWorldScene.h"
#include "TestScene.h"
#include "LoadScene.h"
#define COCOS2D_DEBUG 1
USING_NS_CC;

Scene* GamePlay::startScene(){
  auto gameplay = GamePlay::getInstance();

  return gameplay->getScene(0);

}
GamePlay* GamePlay::m_game = NULL;
GamePlay::GamePlay():currentScene(0),m_arrayindex(-1){
  for(int i=0;i<10;i++){
    m_sceneArray[i] = NULL;
  }
}

GamePlay* GamePlay::getInstance(){
  if(m_game == NULL){
    m_game = new GamePlay();
    m_game->init();
    return m_game;
  }
  return m_game;
}

GamePlay::~GamePlay(){
  if(m_game != NULL){
    delete m_game;m_game=NULL;
  }
    
}

bool GamePlay::addScene(Scene* scene){
  if( currentScene >= 9){
    return false;
  }
  m_arrayindex++;
  m_sceneArray[m_arrayindex] = scene;
  return true;
}

bool GamePlay::addLoadScene(LoadScene* scene){
  if(currentScene >= 8){//we need add two
    return false;
  }
  m_arrayindex++;
  m_sceneArray[m_arrayindex] = scene;
  m_arrayindex++;
  m_sceneArray[m_arrayindex] = scene->getUserScene();
  return true;
}


void GamePlay::NextScene(){
  if(currentScene >= m_arrayindex){//no more
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
  }
  currentScene++;
  CCLOG("current scene :%d",currentScene);
  Director::getInstance()->replaceScene(TransitionFade::create(2,m_sceneArray[currentScene]));
}



bool GamePlay::init(){
  //init others, like layers, players, and data or something
  //now we only need add scene, gameplay init with sample scene
  auto u_scene = TestScene::create();
  auto load = LoadScene::create(u_scene);


  addLoadScene(load);
  return true;
  
}
