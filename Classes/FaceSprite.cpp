#include "FaceSprite.h"

#include "KFCommonDefinition.h"

USING_NS_CC;

void FaceSprite::showScared()
{
	setTexture(_scaredFace);
}

void FaceSprite::showHitting()
{
	setTexture(_hittingFace);
}

void FaceSprite::showHurt()
{
	setTexture(_hurtFace);
}

bool FaceSprite::init()
{
	if (Sprite::initWithFile("face1.png") == false)
	{
		return false;
	}

	_scaredFace = this->getTexture();
	_hittingFace = Director::getInstance()->getTextureCache()->addImage("face2.png");
	_hurtFace = Director::getInstance()->getTextureCache()->addImage("face3.png");

	auto size = getContentSize();
	const auto physicsBody = PhysicsBody::createCircle(size.width / 2, PhysicsMaterial(0.5f, 1.0f, 0.0f));
	physicsBody->setContactTestBitmask(FACE_BIT_MASK);
	addComponent(physicsBody);

	return true;
}
