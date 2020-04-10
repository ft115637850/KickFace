#pragma once
#include "Background.h"
#include "cocos2d.h"
#include "FaceSprite.h"
#include "HammerSprite.h"
#include "KickMap.h"

USING_NS_CC;

class KickFaceScene: public Scene
{
private:
	std::unordered_map<int, cocos2d::Node*> _mouses;
	HammerSprite* _hammer;
	FaceSprite* _face;
	KickMap* _tileMap;
	Size _worldSize;
	Size _visibleSize;
	Background* _background;
	Node* _boundary;
	std::chrono::time_point<std::chrono::steady_clock> enterFireTime;
	std::chrono::time_point<std::chrono::steady_clock> exitFireTime;
	bool onTouchHammerBegan(cocos2d::Touch* touch, cocos2d::Event* e);
	void onTouchHammerMoved(cocos2d::Touch* touch, cocos2d::Event* e);
	void onTouchHammerEnded(cocos2d::Touch* touch, cocos2d::Event* e);
	bool onBodyContact(cocos2d::PhysicsContact& contact);
	void onBodySeparate(cocos2d::PhysicsContact& contact);
	void kickComplete();
	void createWorldAndMap();
	void addFace();
	void addKickWeapon();
	void addEventHandlers();
	KickFaceScene();
	virtual ~KickFaceScene();
public:
	bool init() override;
	void onEnterTransitionDidFinish() override;
	CREATE_FUNC(KickFaceScene);
};

