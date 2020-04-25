#pragma once
#include "cocos2d.h"

class CoinSprite : public cocos2d::Sprite
{
public:
	void getCoin();
	bool init() override;
	CREATE_FUNC(CoinSprite);
	CoinSprite();
	~CoinSprite();
};

