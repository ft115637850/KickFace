#include "CoinSprite.h"

#include "KFCommonDefinition.h"

USING_NS_CC;

unsigned CoinSprite::getCoin()
{
	auto action1 = JumpBy::create(0.5, Vec2(0, 0), 80, 1);
	auto action2 = Sequence::create(
		ScaleTo::create(0.25f, 0, 1.0f),
		ScaleTo::create(0.25f, 1.0f, 1.0f),
		CallFunc::create([this]() {this->removeFromParent();}),
		NULL);
	auto action3 = FadeOut::create(0.5);
	Vector<FiniteTimeAction*> actions;
	actions.pushBack(action1);
	actions.pushBack(action2);
	actions.pushBack(action3);

	this->runAction(Spawn::create(actions));
	return 10;
}

bool CoinSprite::init()
{
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	auto f = Director::getInstance()->getContentScaleFactor();
	float textureSize = 32 / f;
	float textureXIdx = 6;
	float textureYIdx = 10;
	auto frame0 = SpriteFrame::createWithTexture(texture, Rect(textureSize * textureXIdx, textureSize * textureYIdx, textureSize, textureSize));
	if (Sprite::initWithSpriteFrame(frame0) == false)
	{
		return false;
	}

	auto size = getContentSize();
	const auto physicsBody = PhysicsBody::createCircle(size.width / 2, COIN_MATERIAL);
	physicsBody->setContactTestBitmask(COIN_BIT_MASK);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	addComponent(physicsBody);
	//
	//this->runAction(RepeatForever::create(
	//	Sequence::create(
	//		ScaleTo::create(0.25f, 0, 1.0f), ScaleTo::create(0.25f, 1.0f, 1.0f), NULL)));
	return true;
}

CoinSprite::CoinSprite()
{
}


CoinSprite::~CoinSprite()
{
}
