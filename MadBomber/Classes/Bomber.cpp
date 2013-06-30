#include "Bomber.h"
#include "CCActionInterval.h"
#include "CCPointExtension.h"
#include "CCActionInstant.h"
#include "CCDirector.h"
#include "MainGame.h"

Bomber::~Bomber()
{
  CC_SAFE_RELEASE(levels);
}

bool Bomber::init()
{
  if (!Sprite::initWithFile("placeholder.png"))
    return false;

  setTextureRect(CCRectMake(0, 0, 50, 100));
  setColor(ccc3(255, 255, 255));
 
  reset();
  
  return true;
}

void Bomber::startBombing()
{
  Dictionary *level = (Dictionary *)levels->objectAtIndex(currentLevel);
  bombsRemaining = level->valueForKey("numBombs")->intValue();
  moveToNewSpot();
}

int Bomber::randomValueBetween(int low, int high) {
  return (rand() % high) + low;
}

void Bomber::moveToNewSpot()
{
  Size size = Director::sharedDirector()->getWinSize();

  Dictionary *level = (Dictionary *)levels->objectAtIndex(currentLevel);
  int unitsPerSecond = level->valueForKey("unitsPerSecond")->intValue(); 
  int randomNextLocation = randomValueBetween(25, size.width - 25);
  int distance = randomNextLocation - getPositionX();

  FiniteTimeAction *dropBomb = Sequence::create(
      MoveTo::create(abs((float) distance / (float) unitsPerSecond), ccp(randomNextLocation, getPositionY())),
      CallFunc::create(this, callfunc_selector(Bomber::dropBomb)),
      NULL
  );
  runAction(dropBomb);
}

void Bomber::dropBomb()
{
  Dictionary *level = (Dictionary *)levels->objectAtIndex(currentLevel);
  int value = level->valueForKey("value")->intValue();
  
  ((MainGame *)getParent())->dropBomb(ccp(this->getPositionX(), this->getPositionY() - 50), value);
  bombsRemaining--;

  if (!doneBombing())
  {
    moveToNewSpot();
  }
}

void Bomber::bombHit()
{
  if (currentLevel > 0)
    currentLevel--;
  stopAllActions();
}

void Bomber::increaseLevel()
{
  if (currentLevel < levels->count() - 1)
    currentLevel++;
}

bool Bomber::doneBombing()
{
  return bombsRemaining == 0;
}

void Bomber::reset()
{
  CC_SAFE_RELEASE(levels);
  std::string levelsFile = FileUtils::sharedFileUtils()->fullPathForFilename("levels.plist");
  levels = cocos2d::Array::createWithContentsOfFileThreadSafe(levelsFile.c_str());
  levels->retain();
  currentLevel = 0;
}