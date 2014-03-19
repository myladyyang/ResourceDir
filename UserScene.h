#ifndef __USER_SCENE_H_
#define __USER_SCENE_H_

#include "cocos2d.h"
#include "SysLayer.h"
#include "WorldLayer.h"
#include "Valkyrie.h"
#include "BattleLayer.h"
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
  

  bool initCache(const std::string jsonfile);
  
  float getInitPercent(){return m_percent;}

  static Scene* create();

 protected:

  bool b_init;
  void onNodeTouchedBegan(cocos2d::Node*,cocos2d::Point);
  void onNodeTouchedEnd(cocos2d::Node*);
  void onWorldTouchedBegan(cocos2d::Point);
  void onWorldTouchedEnd();

  void onButtonClick(BT_NUM bn);

  void initProgress(float percent);

  virtual bool SceneBuild();
  //if you don't use initCahe, use this
  void setinit(bool init){b_init = init;}
#if CC_USE_PHYSICS
  void update(float dt) override;
#endif
  UserScene();
  ~UserScene();
  friend class WorldLayer;
 private:

  float m_percent;
  void scheduleMove(float dt);
  Valkyrie * player;
  WorldLayer * worldlayer;
  SysLayer * syslayer;
  
  BattleLayer* battlelayer;

  cocos2d::Point pp;//player position
  cocos2d::Size WorldSize;
  cocos2d::Size ScreenSize;
  
};



#endif
