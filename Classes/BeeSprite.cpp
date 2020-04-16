#include "BeeSprite.h"
#include "KFCommonDefinition.h"
USING_NS_CC;

Vector<BeeSprite*> BeeSprite::beesGroup_;

void BeeSprite::hurt()
{
	this->stopAction(_flyAct);
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	this->setSpriteFrame(SpriteFrame::createWithTexture(texture, Rect(_textureSize * (_textureXIdx + 2), _textureSize * _textureYIdx, _textureSize, _textureSize)));
}

void BeeSprite::startChasingFace(FaceSprite* face)
{
	if (_chasingFace == nullptr)
		_chasingFace = face;

	this->schedule(schedule_selector(BeeSprite::updateChase), 0.5f);
}

void BeeSprite::applyChasingForce(const cocos2d::Vec2 & distance)
{
	adjustDirection(distance);

	float factor = 200;
	if ((abs(distance.x) < abs(distance.y) && abs(distance.y) < 400) ||
		(abs(distance.x) > abs(distance.y) && abs(distance.x) < 400))
	{
		factor = 500;
	}
	else if ((abs(distance.x) < abs(distance.y) && abs(distance.y) > 1000) ||
		(abs(distance.x) > abs(distance.y) && abs(distance.x) > 1000))
	{
		factor = 1;
	}

	this->getPhysicsBody()->applyForce(this->getPhysicsBody()->getMass() * distance * factor);
}

void BeeSprite::adjustDirection(const cocos2d::Vec2 & distance)
{
	if (distance.x < 0)
	{
		if (isTowardLeft == false)
		{
			this->setFlippedX(false);
			isTowardLeft = true;
		}

		if (!_chasingParticleLeft->isActive())
		{
			_chasingParticleLeft->start();
		}

		if (_chasingParticleRight->isActive())
		{
			_chasingParticleRight->stop();
		}
	}
	else if (distance.x > 0)
	{
		if (isTowardLeft == true)
		{
			this->setFlippedX(true);
			isTowardLeft = false;
		}

		if (!_chasingParticleRight->isActive())
		{
			_chasingParticleRight->start();
		}

		if (_chasingParticleLeft->isActive())
		{
			_chasingParticleLeft->stop();
		}
	}
}

void BeeSprite::addParticle()
{
	auto pFileLeft = FileUtils::getInstance()->getValueMapFromFile("particle_bee_l.plist");
	_chasingParticleLeft = ParticleSystemQuad::create(pFileLeft);
	//_chasingParticleLeft->setAutoRemoveOnFinish(true);
	_chasingParticleLeft->setStartColor(Color4F::WHITE);
	_chasingParticleLeft->setEndColor(Color4F::WHITE);
	_chasingParticleLeft->setPosition(0, 0);
	_chasingParticleLeft->setPositionType(ParticleSystem::PositionType::RELATIVE);
	_chasingParticleLeft->stop();
	addChild(_chasingParticleLeft);

	auto pFileRight = FileUtils::getInstance()->getValueMapFromFile("particle_bee_r.plist");
	_chasingParticleRight = ParticleSystemQuad::create(pFileRight);
	//_chasingParticleRight->setAutoRemoveOnFinish(true);
	_chasingParticleRight->setStartColor(Color4F::WHITE);
	_chasingParticleRight->setEndColor(Color4F::WHITE);
	_chasingParticleRight->setPosition(getContentSize().width, 0);
	_chasingParticleRight->setPositionType(ParticleSystem::PositionType::RELATIVE);
	_chasingParticleRight->stop();
	addChild(_chasingParticleRight);
}

void BeeSprite::collidedWithFace(FaceSprite * face)
{
	if (isRecovered == false)
	{
		return;
	}

	isRecovered = false;
	
	float lossConscious = 1.0f;
	if (_chasingFace == nullptr)
	{
		_chasingFace = face;
		hurt();
		BeeSprite::notifyGroupChasing(face);
	}
	else
	{
		if (_chasingParticleLeft->isActive())
		{
			_chasingParticleLeft->stop();
		}

		if (_chasingParticleRight->isActive())
		{
			_chasingParticleRight->stop();
		}

		
		lossConscious = 0.8f;
		this->unschedule(schedule_selector(BeeSprite::updateChase));
	}

	this->runAction(Sequence::create(DelayTime::create(lossConscious),
		CallFunc::create(CC_CALLBACK_0(BeeSprite::recoverFromCollision, this)),
		CallFunc::create(CC_CALLBACK_0(BeeSprite::startChasingFace, this, face)),
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
	isRecovered = true;
	if (_chasingFace == nullptr)
		return;

	auto targetPosition = _chasingFace->getPosition() / MAP_SCALE_FACTOR;
	auto beePosition = this->getPosition();
	Vec2 distance = (targetPosition - beePosition);

	applyChasingForce(distance);
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

void BeeSprite::clearBeesGroup()
{
	beesGroup_.clear();
}

void BeeSprite::notifyGroupChasing(FaceSprite* face)
{
	for (auto bee: beesGroup_)
	{
		if (bee->_chasingFace == nullptr)
		{
			bee->startChasingFace(face);
		}
	}
}

bool BeeSprite::initBeeSprite(unsigned beeType)
{
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

	addParticle();

	beesGroup_.pushBack(this);
	return true;
}

BeeSprite::~BeeSprite()
{
	_chasingParticleLeft->setAutoRemoveOnFinish(true);
	_chasingParticleLeft->stopSystem();
	_chasingParticleRight->setAutoRemoveOnFinish(true);
	_chasingParticleRight->stopSystem();

	this->unschedule(schedule_selector(BeeSprite::updateChase));
	this->stopAllActions();
}
