#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "LoadScene.h"
//#include "valkyrie.h"
class GamePlay
{
 public:
  //The start scene creator
  static cocos2d::Scene* startScene(float,float);
  
  static GamePlay* getInstance();
  virtual bool init();
  
  virtual void NextScene();
  
  void EndGame(){cocos2d::Director::getInstance()->end();}
  //callbacks
  /* virtual bool TouchesBegan(cocos2d::Touch* touches,cocos2d::Event* event); */
  /* virtual void TouchesEnded(cocos2d::Touch* touches,cocos2d::Event* event); */
  
  /* virtual bool ContactBegan(cocos2d::EventCustom* event, const cocos2d::PhysicsContact& contact); */

  /* void update(float dt) override; */

  /* //android specific */
  /* virtual void keyBackClicked(){}; */
  /* virtual void keyMenuClicked(){}; */

  void BackToMenu(){};
  void end(){cocos2d::Director::getInstance()->end();}
  bool addScene(cocos2d::Scene* scene);
  bool addLoadScene(LoadScene* scene);
  void setRatio(float,float);
  static GamePlay* m_game;
 private:
  //single
  GamePlay();
  virtual ~GamePlay();
  cocos2d::Scene* getScene(int index){return m_sceneArray[index];}
    

  /* Valkyrie * m_lenneth;//Valkyrie inherit from cocostudio::Armature */
  /* Room * m_room; //Room contain everything other than valkyrie */
  /* Camera * m_camera;  */
  
  cocos2d::Scene* m_sceneArray[10];
  int currentScene;
  int m_arrayindex;

  float m_rx,m_ry;

};




#endif
