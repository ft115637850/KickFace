#include "FlagSprite.h"

#include "KFCommonDefinition.h"

USING_NS_CC;

FlagSprite * FlagSprite::createFlagSprite(unsigned flagColor)
{
	FlagSprite* p = new FlagSprite();
	if (p && p->initFlagSprite(flagColor))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool FlagSprite::initFlagSprite(unsigned flagColor)
{
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	const float textureXIdx = 6;
	const float textureYIdx = 11.0f + flagColor;

	auto f = Director::getInstance()->getContentScaleFactor();
	const float textureSize = 32 / f;
	const auto frame0 = SpriteFrame::createWithTexture(texture, Rect(textureSize * textureXIdx, textureSize * textureYIdx, textureSize, textureSize));
	const auto frame1 = SpriteFrame::createWithTexture(texture, Rect(textureSize * (textureXIdx + 1), textureSize * textureYIdx, textureSize, textureSize));

	if (Sprite::initWithSpriteFrame(frame0) == false)
	{
		return false;
	}

	Vector<cocos2d::SpriteFrame *> frame;
	frame.pushBack(frame0);
	frame.pushBack(frame1);

	const auto animation = Animation::createWithSpriteFrames(frame, 0.3f);
	this->runAction(RepeatForever::create(Animate::create(animation)));
	return true;
}

FlagSprite::FlagSprite()
{
}


FlagSprite::~FlagSprite()
{
	stopAllActions();
}
