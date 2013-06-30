#include "MainGame.h"
#include "SimpleAudioEngine.h"
#include "Buckets.h"
#include "Bomber.h"
#include "Bomb.h"

using namespace cocos2d;
using namespace CocosDenshion;

typedef enum _tags {
  kMenu = 10
} tags;

MainGame::~MainGame()
{
  CC_SAFE_RELEASE(bomber);
  CC_SAFE_RELEASE(bombs);
  CC_SAFE_RELEASE(pBuckets);
  CC_SAFE_RELEASE(scoreLabel);
}

Scene *MainGame::scene() {
  // 'scene' is an autorelease object
  Scene *scene = Scene::create();

  // 'layer' is an autorelease object
  MainGame *layer = MainGame::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init() {
  //////////////////////////////
  // 1. super init first
  if (!Layer::init()) {
    return false;
  }

  // ask director the window size
  Size size = Director::sharedDirector()->getWinSize();
  Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate((cocos2d::TargetedTouchDelegate *)this, 0, true);
  
  LabelTTF* label = LabelTTF::create("New Game", "Arial", 28);
  MenuItemLabel* gameOver = MenuItemLabel::create(label, this, menu_selector(MainGame::newGame));
  
  Menu *menu = Menu::createWithItem(gameOver);
  
  menu->alignItemsHorizontally();
  menu->setVisible(true);

  Sprite *pSprite = Sprite::create("background.png");
  pBuckets = Buckets::create();
  pBuckets->retain();
  bomber = Bomber::create();
  bomber->retain();
  
  scoreLabel = LabelTTF::create("0", "Arial", 32);
  scoreLabel->setPosition(ccp(950, 730));
  scoreLabel->retain();

  // position the sprite on the center of the screen
  pSprite->setPosition(ccp(size.width / 2, size.height / 2));
  positionBomberAndBuckets();
 
  addChild(pSprite, 0);
  addChild(scoreLabel, 1);
  addChild(pBuckets, 1);
  addChild(bomber, 1);
  addChild(menu, 2, kMenu);

  bombs = cocos2d::Array::createWithCapacity(10);
  bombs->retain();
  score = 0;

  this->schedule(schedule_selector(MainGame::update));

  return true;
}

void MainGame::dropBomb(const cocos2d::Point &location, int value)
{
  Bomb *bomb = Bomb::create(location, value);

  FiniteTimeAction *droppingBomb = Sequence::create(
      MoveTo::create(3.0, ccp(location.x, 0)),
      CallFuncN::create(this, callfuncN_selector(MainGame::bombHitGround)),
      NULL
  );
  bomb->runAction(droppingBomb);
  getParent()->addChild(bomb);
  bombs->addObject(bomb);
}

void MainGame::update(float dt)
{
  int count = bombs->count();

  // Count downward so we can remove bombs on the fly
  for(int i = count - 1; i >= 0; i--)
  {
    Bomb *bomb = (Bomb *) bombs->objectAtIndex(i);

    if (pBuckets->intersects(bomb))
    {
      bomb->stopAllActions();
      bomb->setVisible(false);

      bombs->removeObjectAtIndex(i);
      score += bomb->value();
      scoreLabel->setString(cocos2d::String::createWithFormat("%d", score)-> getCString());
      
      if (bomber->doneBombing())
      {
        scheduleOnce(schedule_selector(MainGame::increaseLevelAndStartBombing), 2);
      }
    }
  }
}

void MainGame::bombHitGround(Sprite *bomb)
{
  Object *object;
  CCARRAY_FOREACH(bombs, object)
  {
    Bomb *fallingBomb = static_cast<Bomb *>(object);
    fallingBomb->setVisible(false);
    fallingBomb->stopAllActions();
    bombs->removeObject(fallingBomb);
  }
  
  bomber->bombHit();
  pBuckets->removeOne();

  if (pBuckets->empty())
  {
    Node *menu = getChildByTag(kMenu);
    menu->setVisible(true);
  } else {
    scheduleOnce(schedule_selector(MainGame::startBombing), 2);
  }
}

void MainGame::newGame()
{
  Node *menu = getChildByTag(kMenu);
  menu->setVisible(false);
  score = 0;
  pBuckets->reset();
  positionBomberAndBuckets();
  bomber->reset();
  scheduleOnce(schedule_selector(MainGame::startBombing), 2);
}

void MainGame::increaseLevelAndStartBombing()
{
  bomber->increaseLevel();
  bomber->startBombing();
}

void MainGame::startBombing()
{
  bomber->startBombing();
}

void MainGame::positionBomberAndBuckets()
{
  Size size = Director::sharedDirector()->getWinSize();

  pBuckets->setPosition(ccp(size.width / 2, 90));
  bomber->setPosition(ccp(size.width / 2, 644));
}

// Add some levels
// web it
// Try on iPad

// Before true release:
// A max distance (no min)
// More play testing
// Graphics (bombs exploding on hit, and replace the placeholder graphics).
// Sounds
// Font
// Is that time to clean up code? mayhap?