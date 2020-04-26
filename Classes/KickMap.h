#pragma once

#include "cocos2d.h"
#include "FaceSprite.h"
#include "Background.h"
USING_NS_CC;

class KickMap : public Node
{
private:
	float device_scale_factor_ = 1;
	TMXTiledMap* _tiledMap;
	void addPolygonShape(PhysicsBody * phy, ValueVector &points);
	void addSprites(TMXObjectGroup* group);
	void addGrounds(TMXObjectGroup* group);
	void addProps(TMXObjectGroup* group);
	void addFire(TMXObjectGroup* group, Background* bg);
	void addFireRange(TMXObjectGroup* group);
	void addWater(TMXObjectGroup* group);
	void addCactus(TMXObjectGroup* group);
	void addPass(TMXObjectGroup* group);
public:
	Vec2 getOuterSpritesStartPosition(const std::string& spriteName) const;
	~KickMap();
	static KickMap* createKickMap(Background* bg, unsigned levelNumber);
	bool initKickMap(Background* bg, unsigned levelNumber);
};

