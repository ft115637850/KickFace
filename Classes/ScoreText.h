#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ScoreText :public cocos2d::Node
{
protected:
	cocos2d::ui::TextAtlas* _text;
	unsigned _score;
public:
	ScoreText();
	~ScoreText();
	bool init() override;
	void updateView(unsigned value);
	CREATE_FUNC(ScoreText);
};

