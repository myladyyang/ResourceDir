#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
class HelloWorld : public cocos2d::CCLayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Object* pSender);
    
    void spriteMoveFinished(cocos2d::Node*);
    void TouchesEnded(cocos2d::Touch* touches,cocos2d::Event* event);
    // implement the "static create()" method manually
    bool TouchesBegan(cocos2d::Touch* touches,cocos2d::Event* event);
    //test
    void MoveStep(cocos2d::Point*,cocos2d::Point*);
    void ActionClean();
    void ActionStart();
    CREATE_FUNC(HelloWorld);
 private:
    void LongTouch(float dt);
    kmVec2 onestep;
    bool inaction;
    bool locked;
    cocos2d::Size screen;
    cocostudio::Armature * player;
    cocos2d::Sprite* background;

};

#endif // __HELLOWORLD_SCENE_H__
