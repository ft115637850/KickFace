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

	auto bg = Sprite::create("background.png");
	bg->setAnchorPoint(Vec2(0, 0));
	setContentSize(bg->getContentSize());
	addChild(bg);
	return true;
}
