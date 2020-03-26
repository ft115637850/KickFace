#include "HammerSprite.h"
#include "PhysicsShapeCache.h"

bool HammerSprite::init()
{
	if (Sprite::initWithFile("hammer.png") == false)
	{
		return false;
	}

	//After follow face action, the position of this body is wrong. why??
	const auto physicsBody = PhysicsBody::createBox(Size(160.0f, 80.0f), PhysicsMaterial(1.0f, 1.0f, 1.0f), Vec2(0, -93));
	//const auto physicsBody = PhysicsBody::createBox(Size(83.0f, 40.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//physicsBody->setPositionOffset(Vec2(0, -50));
	
	addComponent(physicsBody);

	/*auto shapeCache = PhysicsShapeCache::getInstance();
	shapeCache->addShapesWithFile("hammer.plist");
	shapeCache->setBodyOnSprite("hammer.png", this);*/

	return true;
}
