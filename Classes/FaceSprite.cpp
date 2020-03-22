#include "FaceSprite.h"

USING_NS_CC;

bool FaceSprite::init()
{
	if (Sprite::initWithFile("face1.png") == false)
	{
		return false;
	}
	
	const auto physicsBody = PhysicsBody::createCircle(24.0f, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	addComponent(physicsBody);

	return true;
}
