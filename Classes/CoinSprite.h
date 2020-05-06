#pragma once
#include "cocos2d.h"

class CoinSprite : public cocos2d::Sprite
{
private:
	bool isGotten = false;
public:
	unsigned getCoin();
	bool init() override;
	CREATE_FUNC(CoinSprite);
	CoinSprite();
	~CoinSprite();
};

