#include "GamePlay.h"
#include "HelloWorldScene.h"
#include "TestScene.h"
#include "LoadScene.h"
#include "MainMenuScene.h"
#define COCOS2D_DEBUG 1
USING_NS_CC;

Scene* GamePlay::startScene(float ratio_x,float ratio_y){
  auto gameplay = GamePlay::getInstance();
  gameplay->setRatio(ratio_x,ratio_y);
  return gameplay->getScene(0);

}

void GamePlay::setRatio(float ratio_x,float ratio_y){
  m_rx = ratio_x;
  m_ry = ratio_y;
}

GamePlay* GamePlay::m_game = NULL;
GamePlay::GamePlay():currentScene(0),m_arrayindex(-1),m_rx(1.0),m_ry(1.0){
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
  scene->setScaleX(m_rx);
  scene->setScaleY(m_ry);
  m_arrayindex++;
  m_sceneArray[m_arrayindex] = scene;
  return true;
}

bool GamePlay::addLoadScene(LoadScene* scene){
  if(currentScene >= 8){//we need add two
    return false;
  }
  scene->setScaleX(m_rx);
  scene->setScaleY(m_ry);
  m_arrayindex++;
  m_sceneArray[m_arrayindex] = scene;
  CCLOG("load scene added %d", scene->getTag());
  m_arrayindex++;
  m_sceneArray[m_arrayindex] = scene->getUserScene();
  CCLOG("user scene added %d",scene->getUserScene()->getTag());
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
  CCLOG("current scene :%d",m_sceneArray[currentScene]->getTag());
  m_sceneArray[currentScene]->load();
  Director::getInstance()->replaceScene(TransitionFade::create(2,m_sceneArray[currentScene]));
  //  Director::getInstance()->replaceScene(m_sceneArray[currentScene]);
}



bool GamePlay::init(){
  //init others, like layers, players, and data or something
  //now we only need add scene, gameplay init with sample scene
  auto menu = MainMenuScene::create();
  menu->setTag(71);
  auto u_scene = TestScene::create();
  u_scene->setTag(72);
  auto load = LoadScene::create(u_scene);
  load->setTag(73);
  
  addScene(menu);
  addLoadScene(load);


  
  return true;
  
}

void GamePlay::SaveView(){
  kmGLGetMatrix(KM_GL_MODELVIEW,&m_view);
  // CCLOG("view at %f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",m_view.mat[0],m_view.mat[1],m_view.mat[2],m_view.mat[3],m_view.mat[4],m_view.mat[5],m_view.mat[6],m_view.mat[7],m_view.mat[8],m_view.mat[9],m_view.mat[10],m_view.mat[11],m_view.mat[12],m_view.mat[13],m_view.mat[14],m_view.mat[15]);
}


float GamePlay::getSavedY(){
  return m_view.mat[13];
}
float GamePlay::getSavedX(){
  return m_view.mat[12];
}


void GamePlay::FollowNode(Node* node){
  SaveView();
  CCLOG("camera position: %f,%f",getSavedX(),getSavedY());
  CCLOG("player positioin: %f, %f",node->getPosition().x,node->getPosition().y);
  auto nx =   -getSavedX() - node->getPosition().x;
  auto ny =   -getSavedY() - node->getPosition().y;
  Director::getInstance()->setModelView(nx,ny,0);
}

void GamePlay::unFollow(){
  kmMat4 newVec;
  kmGLGetMatrix(KM_GL_MODELVIEW,&newVec);
  auto newx = newVec.mat[12];
  auto newy = newVec.mat[13];
  Director::getInstance()->setModelView(m_view.mat[12] - newx,m_view.mat[13] - newy,0);
}

