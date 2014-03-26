#include "LoadScene.h"
#include "GamePlay.h"
USING_NS_CC;
//a little hack here..
//const unsigned int kSceneFade = 0xFADEFADE;
bool LoadScene::init(UserScene* scene){
  Scene::init();
  b_ended = false;
  setUserScene(scene);
  syslayer = SysLayer::create();
  addChild(syslayer);
  layer = LoadLayer::create();
  addChild(layer);



  this->scheduleUpdate();
  return true;
}
void LoadScene::load(){
  CCLOG("loadscene load");
  p_scene->load();
}

void LoadScene::update(float dt){
  if(b_ended){
    return;
  }
  auto percent = p_scene->getInitPercent();
  layer->setProgress(percent);
  if(percent == 1.0f){
    auto am = Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget();
    CCLOG("am %d",am);
    if (am == 0){
      b_ended = true;
    
      end();
    }
  }
  else{
    CCLOG("user scene is not ready");
  }
}

void LoadScene::end(){
  CCLOG("load scene end");
  GamePlay::getInstance()->NextScene();
}

LoadScene* LoadScene::create(UserScene* scene){
  LoadScene* ret = new LoadScene();

  if(ret && ret->init(scene)){
    ret->autorelease();
    return ret;
  }
  else{
    CC_SAFE_DELETE(ret);
    return nullptr;
  }

}
