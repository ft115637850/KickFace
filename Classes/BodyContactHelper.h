#pragma once
#include "BeeSprite.h"
#include "cocos2d.h"

USING_NS_CC;
class BodyContactHelper
{
public:
	static BeeSprite* getBeeBetweenShapes(PhysicsShape* shapeA, PhysicsShape* shapeB);
	static FaceSprite* getFaceBetweenShapes(PhysicsShape* shapeA, PhysicsShape* shapeB);
};

