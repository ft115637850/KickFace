#pragma once

#include "cocos2d.h"
USING_NS_CC;

class KickMap : public Node
{
private:
	experimental::TMXTiledMap* _tiledMap;
public:
	Vec2 getFaceStartPosition();
	Vec2 getWeaponPosition();
	CREATE_FUNC(KickMap);
	virtual bool init();
};

