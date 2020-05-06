#include "BoxSprite.h"

#include "KFCommonDefinition.h"

USING_NS_CC;

BoxSprite * BoxSprite::createBoxSprite(unsigned boxType)
{
	BoxSprite* p = new BoxSprite();
	if (p && p->initBoxSprite(boxType))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool BoxSprite::initBoxSprite(unsigned boxType)
{
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	const float textureXIdx = 21.0f + boxType;
	const float textureYIdx = 15.0f;

	auto f = Director::getInstance()->getContentScaleFactor();
	auto textureSize = 32 / f;
	const auto frame0 = SpriteFrame::createWithTexture(texture, Rect(textureSize * textureXIdx, textureSize * textureYIdx, textureSize, textureSize));

	if (Sprite::initWithSpriteFrame(frame0) == false)
	{
		return false;
	}

	const auto physicsBody = PhysicsBody::createBox(getContentSize(), BOX_MATERIAL);
	physicsBody->setContactTestBitmask(BOX_BIT_MASK);
	addComponent(physicsBody);
	return true;
}

BoxSprite::BoxSprite()
{
}


BoxSprite::~BoxSprite()
{
}
