#include "Background.h"

bool Background::init()
{
	if (Node::init() == false)
		return false;

	auto bg = Sprite::create("background.png");
	bg->setAnchorPoint(Vec2(0, 0));
	addChild(bg);

	auto originalSize = bg->getContentSize();
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	float scale = 1.0f;

	setContentSize(originalSize*scale);
	setScale(scale);
	setAnchorPoint(Vec2(0, 0));
	return true;
}
