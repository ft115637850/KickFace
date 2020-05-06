#pragma once
#include "cocos2d.h"

class BoxSprite : public cocos2d::Sprite
{
public:
	static BoxSprite* createBoxSprite(unsigned boxType);
	bool initBoxSprite(unsigned boxType);
	BoxSprite();
	~BoxSprite();
};

