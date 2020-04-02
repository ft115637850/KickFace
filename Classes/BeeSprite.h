#pragma once

#include "cocos2d.h"

class BeeSprite : public cocos2d::Sprite
{
private:
	cocos2d::Vector<cocos2d::SpriteFrame *> _frames;
public:
	static BeeSprite* createBeeSprite(int beeType);
	bool initBeeSprite(int beeColor);
	CREATE_FUNC(BeeSprite);
};

