#include "LoadLayer.h"
#include "common.h"
#include <stdio.h>
USING_NS_CC;
bool LoadLayer::init(){
  if(!LayerColor::initWithColor(Color4B::BLACK)){
    return false;
  }

  m_pLabelLoading = LabelTTF::create("Loading...","Arial",25);
  m_pLabelPercent = LabelTTF::create("%0","Arial",25);

  m_pLabelLoading->setPosition(Point(GAME_WIDTH/2,GAME_HEIGHT/2+50));
  m_pLabelPercent->setPosition(Point(GAME_WIDTH/2,GAME_HEIGHT/2));

  this->addChild(m_pLabelPercent);
  this->addChild(m_pLabelLoading);
  
  return true;
}

void LoadLayer::update(float dt){
  char tmp[10];
  
  sprintf(tmp,"%d%%",(int)(percent *100));
  m_pLabelPercent->setString(tmp);
}
