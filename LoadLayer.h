#ifndef _LOAD_LAYER_H__
#define _LOAD_LAYER_H__

#include "cocos2d.h"

class LoadLayer: public cocos2d::LayerColor{
 public:
  virtual bool init() override;
  
  void setProgress(float per){percent = per;}
  void update(float dt) override;
  CREATE_FUNC(LoadLayer);

 private:
  cocos2d::LabelTTF * m_pLabelLoading;
  cocos2d::LabelTTF * m_pLabelPercent;

  float percent;
};

#endif 
