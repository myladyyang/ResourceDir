#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__


#include "cocos2d.h"


class MainMenuScene: public cocos2d::Scene{
 public:
  virtual bool init() override;
  virtual void end();
  virtual void load();
  void EnterGameCallback(cocos2d::Object*);
  CREATE_FUNC(MainMenuScene);
  
};


#endif
