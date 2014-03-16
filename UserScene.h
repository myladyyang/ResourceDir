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


  virtual bool initCache(const std::string jsonfile);

  static Scene* create();
 protected:
  void onNodeTouchedBegan(cocos2d::Node*){}
  void onNodeTouchedEnd(cocos2d::Node*){}
  void onWorldTouchedBegan(cocos2d::Point);
  void onWorldTouchedEnd();
  
  
  
#if CC_USE_PHYSICS
  void update(float dt) override;
#endif
  UserScene();
  ~UserScene();
  friend class WorldLayer;
 private:
  void scheduleMove(float dt);
  Valkyrie * player;
  WorldLayer * worldlayer;
  SysLayer * syslayer;
  cocos2d::Point pp;//player position
  cocos2d::Size WorldSize;
  cocos2d::Size ScreenSize;
  
};



#endif
