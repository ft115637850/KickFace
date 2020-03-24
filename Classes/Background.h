#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Background :public Node
{
public:
	static Background* createBackground(int width, int height);
	bool initBackground(int width, int height);
};

