#pragma once
#include "BeeSprite.h"
#include "cocos2d.h"

USING_NS_CC;
class BodyContactHelper
{
private:
	static BodyContactHelper* _instance;

public:
	static BodyContactHelper* getInstance();
	BeeSprite* getBeeBetweenShapes(PhysicsShape* shapeA, PhysicsShape* shapeB);
	FaceSprite* getFaceBetweenShapes(PhysicsShape* shapeA, PhysicsShape* shapeB);
};

