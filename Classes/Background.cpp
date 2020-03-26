#include "Background.h"

Background * Background::createBackground(int width, int height)
{
	Background* p = new Background();
	if (p && p->initBackground(width, height))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool Background::initBackground(int width, int height)
{
	if (Node::init() == false)
		return false;

	auto bg = Sprite::create("background.png", Rect(0, 0, width, height));
	bg->setAnchorPoint(Vec2(0, 0));
	addChild(bg);
	return true;
}
