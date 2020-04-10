#pragma once

#include "cocos2d.h"

class FaceSprite : public cocos2d::Sprite
{
private:
	bool isOnFire = false;
	cocos2d::Texture2D* _scaredFace = nullptr;
	cocos2d::Texture2D* _hittingFace = nullptr;
	cocos2d::Texture2D* _hurtFace = nullptr;
	cocos2d::ParticleSystemQuad* _smokeEmitter = nullptr;
	cocos2d::ParticleSystemQuad* _fireEmitter = nullptr;
public:
	void showScared();
	void showHitting();
	void showHurt();
	void catchFire();
	void fallInWater();
	bool init() override;
	CREATE_FUNC(FaceSprite);
	~FaceSprite();
};

