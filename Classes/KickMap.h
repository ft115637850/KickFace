#pragma once

#include "cocos2d.h"
#include "FaceSprite.h"
USING_NS_CC;

class KickMap : public Node
{
private:
	TMXTiledMap* _tiledMap;
public:
	Vec2 getOuterSpritesStartPosition(const std::string& spriteName);
	CREATE_FUNC(KickMap);
	bool init() override;
};

