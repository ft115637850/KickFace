#pragma once

#include "cocos2d.h"

class FaceSprite : public cocos2d::Sprite
{
private:
	bool isOnFire = false;
	bool isOnCactus = false;
	cocos2d::Texture2D* _scaredFace = nullptr;
	cocos2d::Texture2D* _hittingFace = nullptr;
	cocos2d::Texture2D* _hurtFace = nullptr;
	cocos2d::ParticleSystemQuad* _smokeEmitter = nullptr;
	cocos2d::ParticleSystemQuad* _fireEmitter = nullptr;
public:
	void hitCactus();
	void showScared();
	void showHitting();
	void showHurt();
	void catchFire();
	void fallInWater();
	void update(float dt) override;
	bool init() override;
	CREATE_FUNC(FaceSprite);
	~FaceSprite();
};

