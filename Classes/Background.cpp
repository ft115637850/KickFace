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

	auto f = Director::getInstance()->getContentScaleFactor();
	setContentSize(Size(width / f, height / f));

	return true;
}
