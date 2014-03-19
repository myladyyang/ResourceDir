#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "Valkyrie.h"
enum class BT_NUM{
  Button_A,
    Button_B,
    Button_C,
    Button_D,
};

class BattleLayer: public cocos2d::LayerColor{
 public:
  virtual bool init();
  virtual void FadeOut();
  virtual void FadeIn();
  BT_NUM  ButtonClick(cocos2d::Point);
  
  CREATE_FUNC(BattleLayer);
 protected:

 private:
  int clicknum;
  
  cocos2d::Sprite * b_act1;
  cocos2d::Sprite * b_act2;
  cocos2d::Sprite * b_act3;
  cocos2d::Sprite * b_act4;

  
  
};


#endif
