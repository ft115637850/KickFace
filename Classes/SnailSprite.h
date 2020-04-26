#pragma once

#include "cocos2d.h"

class SnailSprite : public cocos2d::Sprite
{
private:
	float _textureSize = 1;
	unsigned _snailColor = 1;
	bool _isFalling = false;
public:
	static SnailSprite* createSnail(unsigned snailColor, int angle);
	bool initSnail(unsigned snailColor, int angle);
	void hurt();
	void update(float delta) override;
	SnailSprite();
	~SnailSprite();
};

