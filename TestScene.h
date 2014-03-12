#ifndef  __TEST_SCENE_H__
#define  __TEST_SCENE_H__
#include "UserScene.h"


class TestScene: public UserScene{
 public:
  bool init();
  
  CREATE_FUNC(TestScene);
 private:
  TestScene();

};


#endif
