#include "ScoreText.h"

USING_NS_CC;

ScoreText::ScoreText() : _text(nullptr), _score(0)
{
}

ScoreText::~ScoreText()
{
}

bool ScoreText::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	_text = ui::TextAtlas::create("0", "number.png", 16, 16, "0");
	_text->setAnchorPoint(Vec2(1, 0.5));
	this->addChild(_text);
	return true;
}

void ScoreText::updateView(unsigned value)
{
	if (value == _score)
		return;

	_score = value;
	_text->setString(StringUtils::format("%d", value));
	auto effect = _text->clone();
	this->addChild(effect);
	effect->runAction(Sequence::create(
		Spawn::create(ScaleTo::create(0.25, 2), FadeOut::create(0.25), NULL),
		CallFunc::create([effect]() {effect->removeFromParent(); }),
		NULL));
}
