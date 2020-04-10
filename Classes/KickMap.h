#pragma once

#include "cocos2d.h"
#include "FaceSprite.h"
#include "Background.h"
USING_NS_CC;

class KickMap : public Node
{
private:
	TMXTiledMap* _tiledMap;
	void addBees();
public:
	Vec2 getOuterSpritesStartPosition(const std::string& spriteName);
	CREATE_FUNC(KickMap);
	~KickMap();
	bool init() override;
	void addFire(Background* bg);
};

