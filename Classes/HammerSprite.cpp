#include "HammerSprite.h"
#include "PhysicsShapeCache.h"

bool HammerSprite::init()
{
	if (Sprite::initWithFile("hammer.png") == false)
	{
		return false;
	}

	const auto physicsBody = PhysicsBody::createBox(Size(83.0f, 40.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setPositionOffset(Vec2(0, -50));
	addComponent(physicsBody);

	/*auto shapeCache = PhysicsShapeCache::getInstance();
	shapeCache->addShapesWithFile("hammer.plist");
	shapeCache->setBodyOnSprite("hammer.png", this);*/

	return true;
}
