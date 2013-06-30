#include "CCLayer.h"
#include "CCLabelTTF.h"

USING_NS_CC;

class Buckets : public Layer
{
  SpriteBatchNode *batchNode;
  Point velocity;
  float halfBucketWidth;
  float minPosition;
  float maxPosition;
  
  void resetBuckets();

public:
  virtual bool init();
  virtual void didAccelerate(Acceleration* pAccelerationValue);
  virtual void update(float delta);
  bool intersects(Sprite *sprite);
  void removeOne();
  bool empty();
  void reset();
  ~Buckets();

  CREATE_FUNC(Buckets);
};
