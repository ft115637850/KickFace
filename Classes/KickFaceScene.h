#pragma once
#include "Background.h"
#include "cocos2d.h"
#include "FaceSprite.h"
#include "HammerSprite.h"

USING_NS_CC;

class KickFaceScene: public Scene
{
private:
	std::unordered_map<int, cocos2d::Node*> _mouses;
	HammerSprite* _hammer;
	FaceSprite* _face;
	Size _worldSize;
	Vec2 faceStartPosition;
	Size _visibleSize;
	Action* _followAct;
	Background* _background;
	bool onTouchHammerBegan(cocos2d::Touch* touch, cocos2d::Event* e);
	void onTouchHammerMoved(cocos2d::Touch* touch, cocos2d::Event* e);
	void onTouchHammerEnded(cocos2d::Touch* touch, cocos2d::Event* e);
	bool onBodyContact(cocos2d::PhysicsContact& contact);
	KickFaceScene();
	~KickFaceScene();
public:
	bool init() override;
	void onEnterTransitionDidFinish() override;
	CREATE_FUNC(KickFaceScene);
};

