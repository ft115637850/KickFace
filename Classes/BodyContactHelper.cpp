#include "BodyContactHelper.h"


#include "CoinSprite.h"
#include "KFCommonDefinition.h"
#include "SnailSprite.h"

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

SnailSprite * BodyContactHelper::getSnailBetweenShapes(PhysicsShape * shapeA, PhysicsShape * shapeB)
{
	SnailSprite* sp = nullptr;
	if (shapeA->getContactTestBitmask() == SNAIL_BIT_MASK)
	{
		sp = static_cast<SnailSprite*>(shapeA->getBody()->getNode());
	}
	else
	{
		sp = static_cast<SnailSprite*>(shapeB->getBody()->getNode());
	}
	return sp;
}

CoinSprite * BodyContactHelper::getCoinBetweenShapes(PhysicsShape * shapeA, PhysicsShape * shapeB)
{
	CoinSprite* sp = nullptr;
	if (shapeA->getContactTestBitmask() == COIN_BIT_MASK)
	{
		sp = static_cast<CoinSprite*>(shapeA->getBody()->getNode());
	}
	else
	{
		sp = static_cast<CoinSprite*>(shapeB->getBody()->getNode());
	}
	return sp;
}