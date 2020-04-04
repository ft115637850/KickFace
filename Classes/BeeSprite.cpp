#include "BeeSprite.h"
#include "KFCommonDefinition.h"
USING_NS_CC;

void BeeSprite::hurt()
{
	this->stopAction(_flyAct);
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	this->setSpriteFrame(SpriteFrame::createWithTexture(texture, Rect(_textureSize * (_textureXIdx + 2), _textureSize * _textureYIdx, _textureSize, _textureSize)));
}

void BeeSprite::startChasingFace()
{
	this->schedule(schedule_selector(BeeSprite::updateChase), 0.5f);
}

void BeeSprite::applyChasingForce(const cocos2d::Vec2 & distance)
{
	if (distance.x < 0 && isTowardLeft == false)
	{
		this->setFlippedX(false);
		isTowardLeft = true;
	}
	else if (distance.x > 0 && isTowardLeft == true)
	{
		this->setFlippedX(true);
		isTowardLeft = false;
	}

	float factor = 200;
	if ((abs(distance.x) < abs(distance.y) && abs(distance.y) < 400) ||
		(abs(distance.x) > abs(distance.y) && abs(distance.x) < 400))
	{
		factor = 400;
	}
	else if ((abs(distance.x) < abs(distance.y) && abs(distance.y) > 1000) ||
		(abs(distance.x) > abs(distance.y) && abs(distance.x) > 1000))
	{
		factor = 1;
	}

	this->getPhysicsBody()->applyForce(this->getPhysicsBody()->getMass() * distance * factor);
}

void BeeSprite::collidedWithFace(FaceSprite * face)
{
	float lossConscious = 1.0f;
	if (_chasingFace == nullptr)
	{
		hurt();
		_chasingFace = face;
	}
	else
	{
		lossConscious = 0.8f;
		this->unschedule(schedule_selector(BeeSprite::updateChase));
		this->stopAction(_chaseAct);
	}

	_chaseAct = this->runAction(Sequence::create(DelayTime::create(lossConscious),
		CallFunc::create(CC_CALLBACK_0(BeeSprite::recoverFromCollision, this)),
		CallFunc::create(CC_CALLBACK_0(BeeSprite::startChasingFace, this)),
		NULL));
}

void BeeSprite::recoverFromCollision()
{
	this->stopAction(_flyAct);
	auto animation = Animation::createWithSpriteFrames(_frames, 0.1f);
	_flyAct = this->runAction(RepeatForever::create(Animate::create(animation)));
	
	auto velocity = this->getPhysicsBody()->getVelocity();
	this->getPhysicsBody()->applyImpulse(-1 * this->getPhysicsBody()->getMass() * velocity / 2);

}

void BeeSprite::updateChase(float t)
{
	if (_chasingFace == nullptr)
		return;

	auto targetPosition = _chasingFace->getPosition() / MAP_SCALE_FACTOR;
	auto beePosition = this->getPosition();
	Vec2 distance = (targetPosition - beePosition);

	applyChasingForce(distance);

	/*float r = atan2(distance.y, distance.x) * 180 / PI + 180;
	this->setRotation(r);*/
}

BeeSprite * BeeSprite::createBeeSprite(unsigned beeColor)
{
	BeeSprite* p = new BeeSprite();
	if (p && p->initBeeSprite(beeColor))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool BeeSprite::initBeeSprite(unsigned beeType)
{
	/*auto texture = Director::getInstance()->getTextureCache()->addImage("bee.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, Rect(32 * 0, 32 * beeType, 32, 32));
	auto frame1 = SpriteFrame::createWithTexture(texture, Rect(32 * 1, 32 * beeType, 32, 32));
	auto frame2 = SpriteFrame::createWithTexture(texture, Rect(32 * 2, 32 * beeType, 32, 32));*/
	_beeType = beeType;
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	switch (beeType)
	{
	case BLACK_BEE:
	{
		_textureXIdx = 0;
		_textureYIdx = 31;
		break;
	}
	case YELLOW_BEE:
	{
		_textureXIdx = 3;
		_textureYIdx = 31;
		break;
	}
	case BLUE_BEE:
	{
		_textureXIdx = 0;
		_textureYIdx = 32;
		break;
	}
	case RED_BEE:
	{
		_textureXIdx = 3;
		_textureYIdx = 32;
		break;
	}
	}

	auto f = Director::getInstance()->getContentScaleFactor();
	_textureSize = 32 / f;
	auto frame0 = SpriteFrame::createWithTexture(texture, Rect(_textureSize * _textureXIdx, _textureSize * _textureYIdx, _textureSize, _textureSize));
	auto frame1 = SpriteFrame::createWithTexture(texture, Rect(_textureSize * (_textureXIdx +1), _textureSize * _textureYIdx, _textureSize, _textureSize));
	//_hurtBee = SpriteFrame::createWithTexture(texture, Rect(32 * (_textureXIdx + 2), 32 * _textureYIdx, 32, 32))->getTexture();

	if (Sprite::initWithSpriteFrame(frame0) == false)
	{
		return false;
	}

	_frames.pushBack(frame0);
	_frames.pushBack(frame1);

	auto animation = Animation::createWithSpriteFrames(_frames, 0.1f);
	_flyAct = this->runAction(RepeatForever::create(Animate::create(animation)));

	auto size = getContentSize();
	const auto physicsBody = PhysicsBody::createCircle(size.width / 2, PhysicsMaterial(0.1f, 0.0f, 1.0f));
	/*physicsBody->setCategoryBitmask(BEE_CATEGORY_MASK);
	physicsBody->setCollisionBitmask(BEE_COLLISION_MASK);*/
	physicsBody->setContactTestBitmask(BEE_BIT_MASK);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	addComponent(physicsBody);
	
	//this->setFlippedX(true);
	return true;
}

BeeSprite::~BeeSprite()
{
	this->unschedule(schedule_selector(BeeSprite::updateChase));
	this->stopAllActions();
}
