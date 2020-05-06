#pragma once
#include "BeeSprite.h"
#include "BoxSprite.h"
#include "cocos2d.h"
#include "CoinSprite.h"
#include "SnailSprite.h"

USING_NS_CC;
class BodyContactHelper
{
public:
	static BeeSprite* getBeeBetweenShapes(PhysicsShape* shapeA, PhysicsShape* shapeB);
	static FaceSprite* getFaceBetweenShapes(PhysicsShape* shapeA, PhysicsShape* shapeB);
	static SnailSprite* getSnailBetweenShapes(PhysicsShape * shapeA, PhysicsShape * shapeB);
	static CoinSprite * getCoinBetweenShapes(PhysicsShape * shapeA, PhysicsShape * shapeB);
	static BoxSprite * getBoxBetweenShapes(PhysicsShape * shapeA, PhysicsShape * shapeB);
};

