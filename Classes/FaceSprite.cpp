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

void FaceSprite::catchFire()
{
	if (isOnFire)
		return;

	isOnFire = true;
	auto size = getContentSize();
	auto pFileLeft = FileUtils::getInstance()->getValueMapFromFile("fire_background.plist");
	auto emitter = ParticleSystemQuad::create(pFileLeft);
	emitter->setPosVar(Vec2(30, 2));
	emitter->setStartSize(35);
	emitter->setPositionType(ParticleSystem::PositionType::FREE);
	emitter->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
	emitter->setAutoRemoveOnFinish(true);
	emitter->setPosition(size.width / 2, size.height);
	addChild(emitter);

	auto pFileLeft2 = FileUtils::getInstance()->getValueMapFromFile("fire_foreground.plist");
	auto emitter2 = ParticleSystemQuad::create(pFileLeft2);
	emitter2->setPosVar(Vec2(26, 1));
	emitter2->setStartSize(30);
	emitter2->setPositionType(ParticleSystem::PositionType::FREE);
	emitter2->setAutoRemoveOnFinish(true);
	emitter2->setPosition(size.width / 2, size.height);
	addChild(emitter2);
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
	/*physicsBody->setCategoryBitmask(FACE_CATEGORY_MASK);
	physicsBody->setCollisionBitmask(FACE_COLLISION_MASK);*/
	physicsBody->setContactTestBitmask(FACE_BIT_MASK);
	addComponent(physicsBody);

	return true;
}

FaceSprite::~FaceSprite()
{
}
