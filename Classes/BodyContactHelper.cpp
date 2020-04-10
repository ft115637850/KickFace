#include "BodyContactHelper.h"

#include "KFCommonDefinition.h"

BeeSprite * BodyContactHelper::getBeeBetweenShapes(PhysicsShape * shapeA, PhysicsShape * shapeB)
{
	BeeSprite* beeSp = nullptr;
	if (shapeA->getContactTestBitmask() == BEE_BIT_MASK)
	{
		beeSp = static_cast<BeeSprite*>(shapeA->getBody()->getNode());
	}
	else
	{
		beeSp = static_cast<BeeSprite*>(shapeB->getBody()->getNode());
	}
	return beeSp;
}

FaceSprite * BodyContactHelper::getFaceBetweenShapes(PhysicsShape * shapeA, PhysicsShape * shapeB)
{
	FaceSprite* sp = nullptr;
	if (shapeA->getContactTestBitmask() == FACE_BIT_MASK)
	{
		sp = static_cast<FaceSprite*>(shapeA->getBody()->getNode());
	}
	else
	{
		sp = static_cast<FaceSprite*>(shapeB->getBody()->getNode());
	}
	return sp;
}