#include "FaceSprite.h"

#include "KFCommonDefinition.h"

USING_NS_CC;

void FaceSprite::hitCactus()
{
	getPhysicsBody()->setVelocity(Vec2::ZERO);
	isOnCactus = true;
}

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

void FaceSprite::catchFire()
{
	if (isOnFire)
		return;

	isOnFire = true;
	auto size = getContentSize();
	auto pFileLeft = FileUtils::getInstance()->getValueMapFromFile("fire_background.plist");
	_smokeEmitter = ParticleSystemQuad::create(pFileLeft);
	_smokeEmitter->setPosVar(Vec2(30, 2));
	_smokeEmitter->setStartSize(35);
	_smokeEmitter->setPositionType(ParticleSystem::PositionType::FREE);
	_smokeEmitter->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
	_smokeEmitter->setAutoRemoveOnFinish(true);
	_smokeEmitter->setPosition(size.width / 2, size.height);
	addChild(_smokeEmitter);

	auto pFileLeft2 = FileUtils::getInstance()->getValueMapFromFile("fire_foreground.plist");
	_fireEmitter = ParticleSystemQuad::create(pFileLeft2);
	_fireEmitter->setPosVar(Vec2(26, 1));
	_fireEmitter->setStartSize(30);
	_fireEmitter->setPositionType(ParticleSystem::PositionType::FREE);
	_fireEmitter->setAutoRemoveOnFinish(true);
	_fireEmitter->setPosition(size.width / 2, size.height);
	addChild(_fireEmitter);
}

void FaceSprite::fallInWater()
{
	if (isOnFire)
	{
		_smokeEmitter->stop();
		_fireEmitter->stop();
	}
}

void FaceSprite::update(float dt)
{
	Sprite::update(dt);
	if (isOnCactus)
	{
		getPhysicsBody()->setDynamic(false);
	}
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
	const auto physicsBody = PhysicsBody::createCircle(size.width / 2, FACE_MATERIAL);
	/*physicsBody->setCategoryBitmask(FACE_CATEGORY_MASK);
	physicsBody->setCollisionBitmask(FACE_COLLISION_MASK);*/
	physicsBody->setContactTestBitmask(FACE_BIT_MASK);
	physicsBody->setVelocityLimit(2560.0f);
	physicsBody->setRotationEnable(false);
	addComponent(physicsBody);

	return true;
}

FaceSprite::~FaceSprite()
{
	if (_smokeEmitter !=nullptr)
	{
		_smokeEmitter->stopSystem();
	}
	if (_fireEmitter !=nullptr)
	{
		_fireEmitter->stopSystem();
	}
}
