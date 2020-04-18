#pragma once
#include "cocos2d.h"


class FlagSprite : public cocos2d::Sprite
{
public:
	static FlagSprite* createFlagSprite(unsigned flagColor);
	bool initFlagSprite(unsigned flagColor);
	FlagSprite();
	~FlagSprite();
};

