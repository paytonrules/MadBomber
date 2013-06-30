#include "Buckets.h"
#include "CCSpriteBatchNode.h"
#include "CCPointExtension.h"
#include "CCDirector.h"

typedef enum _buckets {
  kTopBucket,
  kMiddleBucket,
  kBottomBucket
} Bucket;

static const int kBatchNode = 10;

Buckets::~Buckets()
{
  CC_SAFE_RELEASE(batchNode);
}

bool Buckets::init()
{
  if (!Layer::init()) {
    return false;
  }
  setAccelerometerEnabled(true);

  batchNode = SpriteBatchNode::create("bucket.png", 3);
  batchNode->retain();
  addChild(batchNode, 0, kBatchNode);
  
  resetBuckets();
  
  this->schedule(schedule_selector(Buckets::update));

  return true;
}

void Buckets::removeOne()
{
  batchNode->removeChildAtIndex(batchNode->getChildrenCount() - 1, true);
}

void Buckets::didAccelerate(Acceleration* pAccelerationValue)
{
  velocity = ccp(pAccelerationValue->x, 0.0);
}

void Buckets::update(float delta)
{
  float x = clampf(batchNode->getPositionX() + velocity.x * 25.0, minPosition, maxPosition);

  batchNode->setPositionX(x);
}

bool Buckets::intersects(Sprite *sprite)
{
  cocos2d::Array *children = batchNode->getChildren();

  for (int i = 0; i < children->count(); i++)
  {
    Rect boundingBox = ((Sprite *)children->objectAtIndex(i))->boundingBox();
    boundingBox.origin = batchNode->convertToWorldSpace(boundingBox.origin);

    if (boundingBox.intersectsRect(sprite->boundingBox()))
      return true;
  }

  return false;
}

bool Buckets::empty()
{
  return batchNode->getChildrenCount() == 0;
}

void Buckets::reset()
{
  resetBuckets();
}

void Buckets::resetBuckets()
{
  batchNode->removeAllChildrenWithCleanup(true);
  Sprite *sprite = Sprite::createWithTexture(batchNode->getTexture());
  sprite->setPosition(ccp(0, 60));
  batchNode->addChild(sprite, 0, kTopBucket);
  
  sprite = Sprite::createWithTexture(batchNode->getTexture());
  sprite->setPosition(ccp(0, 0));
  batchNode->addChild(sprite, 0, kMiddleBucket);
  
  sprite = Sprite::createWithTexture(batchNode->getTexture());
  sprite->setPosition(ccp(0, -60));
  batchNode->addChild(sprite, 0, kBottomBucket);
    
  velocity = ccp(0.0, 0.0);
  
  Size size = Director::sharedDirector()->getWinSize();
  halfBucketWidth = batchNode->getTexture()->getContentSize().width / 2.0f;
  minPosition = -(size.width / 2) + halfBucketWidth;
  maxPosition = (size.width / 2) - halfBucketWidth;
}


