#include "CCPlatformMacros.h"
#include "CCSprite.h"

USING_NS_CC;

class Bomber : public Sprite
{
  bool droppingBombs;
  void moveToNewSpot();
  int randomValueBetween(int low, int high);
  int currentLevel;
  int bombsRemaining;
  cocos2d::Array *levels;

public:
  ~Bomber();
  CREATE_FUNC(Bomber);
  virtual bool init();
  void startBombing();
  void dropBomb();
  void bombHit();
  bool doneBombing();
  void increaseLevel();
  void reset();

};