#ifndef __WORLD_LAYER_H__
#define __WORLD_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "UserScene.h"
class UserScene;
class WorldLayer:public cocos2d::Layer{
 public:
  virtual bool init();
  
  virtual bool TouchesBegan(cocos2d::Touch* touch,cocos2d::Event* event);
  virtual void TouchesEnded(cocos2d::Touch* touch, cocos2d::Event* event);
  
  virtual bool ContactBegan(cocos2d::EventCustom* event, const cocos2d::PhysicsContact& contact);
  virtual void update(float dt) override;
  void setUserScene(UserScene* scene){userscene=scene;}
  
  cocos2d::Size getWorldSize();
  float getGroundHeight();
  
  
  CREATE_FUNC(WorldLayer);
 private:
  WorldLayer();
  UserScene* userscene;
  cocos2d::Sprite * background;

  cocos2d::Node* m_cTouchNode;

  cocos2d::Node* ground;
};



#endif
