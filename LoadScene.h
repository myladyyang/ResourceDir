#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include "cocos2d.h"
#include "UserScene.h"
#include "LoadLayer.h"
#include "common.h"


class LoadScene:public cocos2d::Scene{
 public:
  virtual bool init(UserScene*) ;
  virtual void end();
  void setUserScene(UserScene* scene){p_scene = scene;}
  UserScene* getUserScene(){return p_scene;};
  static LoadScene * create(UserScene* preparedscene);
  void load() ;
  void update(float dt) override;
 private:
  
  bool b_ended;
  UserScene* p_scene;
  SysLayer * syslayer;
  LoadLayer* layer;
};


#endif
