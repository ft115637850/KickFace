#pragma once

#include "cocos2d.h"
#include "FaceSprite.h"

class BeeSprite : public cocos2d::Sprite
{
private:
	unsigned _textureXIdx = 0;
	unsigned _textureYIdx = 0;
	float _textureSize = 0;
	unsigned _beeType = 0;
	bool isTowardLeft = true;
	FaceSprite * _chasingFace = nullptr;
	cocos2d::Action* _chaseAct = nullptr;
	cocos2d::Action* _flyAct = nullptr;
	cocos2d::Vector<cocos2d::SpriteFrame *> _frames;
	void hurt();
	void recoverFromCollision();
	void startChasingFace();
	void applyChasingForce(const cocos2d::Vec2& distance);
public:
	void collidedWithFace(FaceSprite* face);
	void updateChase(float t);
	static BeeSprite* createBeeSprite(unsigned beeType);
	bool initBeeSprite(unsigned beeColor);
	CREATE_FUNC(BeeSprite);
	~BeeSprite();
};

