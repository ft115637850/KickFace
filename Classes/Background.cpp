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

	auto bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	Texture2D::TexParams tp = { GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT };
	bg->getTexture()->setTexParameters(tp);
	bg->setTextureRect(Rect(0, 0, width, height));
	bg->setScale(2.0f);
	addChild(bg);	

	auto bg2 = Sprite::create("bg2.png");
	bg2->setAnchorPoint(Vec2(0, 0));
	addChild(bg2);
	setAnchorPoint(Vec2(0, 0));
	return true;
}
