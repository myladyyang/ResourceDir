#ifndef __SYS_LAYER_H__
#define __SYS_LAYER_H__

#include "cocos2d.h"


class SysLayer: public cocos2d::Layer{
 public:
  virtual bool init();
  
  virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,cocos2d::Event* event);
  CREATE_FUNC(SysLayer);

 private:
  SysLayer();

};


#endif
