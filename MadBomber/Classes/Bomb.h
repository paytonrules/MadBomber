
#ifndef __MadBomber__Bomb__
#define __MadBomber__Bomb__
#include "cocos2d.h"

USING_NS_CC;

class Bomb : public Sprite
{
  int _value;
  
public:
  int value();
  static Bomb *create(const Point &location, int value);

  
};

#endif 
