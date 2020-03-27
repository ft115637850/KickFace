#include "FaceSprite.h"

USING_NS_CC;

bool FaceSprite::init()
{
	if (Sprite::initWithFile("face1.png") == false)
	{
		return false;
	}
	auto size = getContentSize();
	const auto physicsBody = PhysicsBody::createCircle(size.width / 2, PhysicsMaterial(0.5f, 1.0f, 0.0f));
	addComponent(physicsBody);

	return true;
}
