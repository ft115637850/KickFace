#pragma once

#include "cocos2d.h"
#include "FaceSprite.h"

class BeeSprite : public cocos2d::Sprite
{
private:
	unsigned _textureXIdx = 0;
	unsigned _textureYIdx = 0;
	float _textureSize = 0;
	bool isTowardLeft = true;
	bool isRecovered = true;
	FaceSprite * _chasingFace = nullptr;
	cocos2d::Action* _flyAct = nullptr;
	cocos2d::ParticleSystemQuad* _chasingParticleLeft = nullptr;
	cocos2d::ParticleSystemQuad* _chasingParticleRight = nullptr;
	cocos2d::Vector<cocos2d::SpriteFrame *> _frames;
	static cocos2d::Vector<BeeSprite*> beesGroup_;
	void hurt();
	void recoverFromCollision();
	void startChasingFace(FaceSprite* face);
	void applyChasingForce(const cocos2d::Vec2& distance);
	void adjustDirection(const cocos2d::Vec2& distance);
	void addParticle();
public:
	void collidedWithFace(FaceSprite* face);
	void updateChase(float t);
	static BeeSprite* createBeeSprite(unsigned beeType);
	static void clearBeesGroup();
	static void notifyGroupChasing(FaceSprite* face);
	bool initBeeSprite(unsigned beeColor);
	CREATE_FUNC(BeeSprite);
	~BeeSprite();
};

