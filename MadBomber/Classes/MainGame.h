#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Bomber;
class Buckets;

class MainGame : public Layer, public TargetedTouchDelegate {
  Bomber *bomber;
  cocos2d::Array *bombs;
  Buckets *pBuckets;
  void newGame();
  void positionBomberAndBuckets();
  LabelTTF *scoreLabel;
  int score;
  
  void startBombing();
  void increaseLevelAndStartBombing();


public:
  ~MainGame();

  // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
  virtual bool init();

  // there's no 'id' in cpp, so we recommend to return the class instance pointer
  static cocos2d::Scene *scene();

  void dropBomb(const cocos2d::Point &location, int value);

  virtual void update(float dt);

  void bombHitGround(Sprite *bomb);
  
  // preprocessor macro for "static create()" constructor ( node() deprecated )
  CREATE_FUNC(MainGame);
};

#endif // __HELLOWORLD_SCENE_H__
