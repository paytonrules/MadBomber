#include "Bomb.h"

Bomb *Bomb::create(const Point &location, int value)
{
  Bomb *pSprite = new Bomb();
  if (pSprite && pSprite->initWithFile("placeholder.png", CCRectMake(0, 0, 30, 30)))
  {
    pSprite->autorelease();
    pSprite->setPosition(location);
    pSprite->_value = value;
    return pSprite;
  }
  CC_SAFE_DELETE(pSprite);
  return NULL;
}

int Bomb::value()
{
  return _value;
}