#pragma once
#include "Background.h"
#include "cocos2d.h"
#include "FaceSprite.h"
#include "HammerSprite.h"
#include "KickMap.h"
#include "ScoreText.h"

USING_NS_CC;

class KickFaceScene: public Scene
{
private:
	unsigned level_number_ = 0;
	unsigned current_level_score_ = 0;
	unsigned start_score_ = 0;
	std::unordered_map<int, cocos2d::Node*> _mouses;
	HammerSprite* _hammer;
	FaceSprite* _face;
	KickMap* _tileMap;
	Size _worldSize;
	Size _visibleSize;
	Background* _background;
	Node* _boundary;
	ScoreText* _scoreText;
	/*std::chrono::time_point<std::chrono::steady_clock> enterFireTime;
	std::chrono::time_point<std::chrono::steady_clock> exitFireTime;*/
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
	void addScoreText();
	void addSpray(const Vec2& position);
	KickFaceScene();
	virtual ~KickFaceScene();
public:
	void onEnterTransitionDidFinish() override;
	static KickFaceScene* createKickFaceScene(unsigned levelNumber = 1, unsigned startScore = 0);
	bool initKickFaceScene(unsigned levelNumber, unsigned startScore);
};

