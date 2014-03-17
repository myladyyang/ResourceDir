#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"


class BattleLayer: public cocos2d::LayerColor{
 public:
  virtual bool init();
  virtual void FadeOut();
  CREATE_FUNC(BattleLayer);

 private:
  
  
  cocos2d::Sprite * b_act1;
  cocos2d::Sprite * b_act2;
  cocos2d::Sprite * b_act3;
  cocos2d::Sprite * b_act4;

  cocos2d::Point pos_layer;
  
};


#endif
