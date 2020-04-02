#include "BeeSprite.h"
#include "KFCommonDefinition.h"
USING_NS_CC;

BeeSprite * BeeSprite::createBeeSprite(int beeColor)
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

bool BeeSprite::initBeeSprite(int beeType)
{
	/*auto texture = Director::getInstance()->getTextureCache()->addImage("bee.png");
	auto frame0 = SpriteFrame::createWithTexture(texture, Rect(32 * 0, 32 * beeType, 32, 32));
	auto frame1 = SpriteFrame::createWithTexture(texture, Rect(32 * 1, 32 * beeType, 32, 32));
	auto frame2 = SpriteFrame::createWithTexture(texture, Rect(32 * 2, 32 * beeType, 32, 32));*/

	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("tiled/32x32.png");
	unsigned xIdx = 0;
	unsigned yIdx = 0;
	switch (beeType)
	{
	case BLACK_BEE:
	{
		xIdx = 0;
		yIdx = 31;
		break;
	}
	case YELLOW_BEE:
	{
		xIdx = 3;
		yIdx = 31;
		break;
	}
	case BLUE_BEE:
	{
		xIdx = 0;
		yIdx = 32;
		break;
	}
	case RED_BEE:
	{
		xIdx = 3;
		yIdx = 32;
		break;
	}
	}

	auto frame0 = SpriteFrame::createWithTexture(texture, Rect(32 * xIdx, 32 * yIdx, 32, 32));
	auto frame1 = SpriteFrame::createWithTexture(texture, Rect(32 * (xIdx+1), 32 * yIdx, 32, 32));
	//auto frame2 = SpriteFrame::createWithTexture(texture, Rect(32 * (xIdx+2), 32 * yIdx, 32, 32));

	if (Sprite::initWithSpriteFrame(frame0) == false)
	{
		return false;
	}

	_frames.pushBack(frame0);
	_frames.pushBack(frame1);

	auto animation = Animation::createWithSpriteFrames(_frames, 0.1f);
	this->runAction(RepeatForever::create(Animate::create(animation)));

	auto size = getContentSize();
	const auto physicsBody = PhysicsBody::createCircle(size.width / 2, PhysicsMaterial(0.1f, 0.0f, 1.0f));
	/*physicsBody->setCategoryBitmask(BEE_CATEGORY_MASK);
	physicsBody->setCollisionBitmask(BEE_COLLISION_MASK);*/
	physicsBody->setContactTestBitmask(BEE_BIT_MASK);
	physicsBody->setGravityEnable(false);
	addComponent(physicsBody);
	
	//this->setFlippedX(true);
	return true;
}