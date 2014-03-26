#ifndef  __TEST_SCENE_H__
#define  __TEST_SCENE_H__
#include "UserScene.h"


class TestScene: public UserScene{
 public:
  virtual bool init() override;
  bool SceneBuild() override;
  virtual void load() override;
  CREATE_FUNC(TestScene);
 private:
  TestScene();

};


#endif
