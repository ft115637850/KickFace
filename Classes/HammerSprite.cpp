#include "HammerSprite.h"

#include "KFCommonDefinition.h"
#include "PhysicsShapeCache.h"

bool HammerSprite::init()
{
	if (Sprite::initWithFile("hammer.png") == false)
	{
		return false;
	}

	auto size = getContentSize();
	const float headerHeightFactor = 112.0f / 403.0f;
	const float headerOffsetFactor = 145.5f / 403.0f;

	const auto physicsBody = PhysicsBody::createBox(Size(size.width, size.height*headerHeightFactor),
		HAMMER_MATERIAL, Vec2(0, -1 * headerOffsetFactor*size.height));
	addComponent(physicsBody);

	return true;
}
