#ifndef __USER_SCENE_H_
#define __USER_SCENE_H_

#include "cocos2d.h"
#include "SysLayer.h"
#include "WorldLayer.h"
#include "Valkyrie.h"
#include "common.h"
class WorldLayer;

class UserScene :public cocos2d::Scene{
  
 public:
  virtual bool init() override;
  virtual void end();

  //static Scene* createWithPhysics();
  virtual WorldLayer* getWorldLayer() ;
  virtual void AddNodetoWorld(Node*,int);
  void addPlayer(Valkyrie * p);
  void setPlayerPostion(cocos2d::Point pos);

  virtual bool initCache(const std::string jsonfile);

  static Scene* create();
 protected:
  void onNodeTouchedBegan(cocos2d::Node*){}
  void onNodeTouchedEnd(cocos2d::Node*){}
  void onWorldTouchedBegan(cocos2d::Point){CCLOG("world in scene touched");}
  void onWorldTouchedEnd(cocos2d::Point){CCLOG("world in scene ended");}
  
#if CC_USE_PHYSICS
  void update(float dt) override;
#endif
  UserScene();
  ~UserScene();
  friend class WorldLayer;
 private:
  Valkyrie * player;
  WorldLayer * worldlayer;
  SysLayer * syslayer;
  cocos2d::Point pp;//player position
  cocos2d::Size WorldSize;
  cocos2d::Size ScreenSize;
  
};



#endif
