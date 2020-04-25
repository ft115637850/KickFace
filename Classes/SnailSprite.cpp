#include "SnailSprite.h"

#include "KFCommonDefinition.h"

USING_NS_CC;

SnailSprite * SnailSprite::createSnail(unsigned snailColor)
{
	SnailSprite* p = new SnailSprite();
	if (p && p->initSnail(snailColor))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool SnailSprite::initSnail(unsigned snailColor)
{
	_snailColor = snailColor;
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	const float textureXIdx = (_snailColor - 1) * 4;
	const float textureYIdx = 33.0f;
	
	auto f = Director::getInstance()->getContentScaleFactor();
	_textureSize = 32 / f;
	const auto frame0 = SpriteFrame::createWithTexture(texture, Rect(_textureSize * textureXIdx, _textureSize * textureYIdx, _textureSize, _textureSize));
	
	if (Sprite::initWithSpriteFrame(frame0) == false)
	{
		return false;
	}

	const auto physicsBody = PhysicsBody::createCircle(getContentSize().width / 2, COIN_MATERIAL);
	physicsBody->setContactTestBitmask(SNAIL_BIT_MASK);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	addComponent(physicsBody);
	return true;
}

void SnailSprite::hurt()
{
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	const float textureXIdx = (_snailColor - 1) * 4;
	const float textureYIdx = 33.0f;
	const auto frame = SpriteFrame::createWithTexture(texture, Rect(_textureSize * (textureXIdx + 2), _textureSize * textureYIdx, _textureSize, _textureSize));
	this->setSpriteFrame(frame);
	
	auto action1 = JumpBy::create(1, Vec2(80, 0), 80, 1);
	auto action2 = RotateBy::create(2, 720);
	Vector<FiniteTimeAction*> actions;
	actions.pushBack(action1);
	actions.pushBack(action2);

	this->runAction(Spawn::create(actions));
	_isFalling = true;
}

void SnailSprite::update(float delta)
{
	Sprite::update(delta);
	if (_isFalling && !this->getPhysicsBody()->isGravityEnabled())
	{
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

SnailSprite::SnailSprite()
{
}


SnailSprite::~SnailSprite()
{
}
