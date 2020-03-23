#include "KickMap.h"

Vec2 KickMap::getFaceStartPosition()
{
	auto objectGroup = _tiledMap->getObjectGroup("sprites");
	auto face = objectGroup->getObject("face");
	
	return Vec2(face["x"].asFloat(), face["y"].asFloat());
}

Vec2 KickMap::getWeaponPosition()
{
	auto objectGroup = _tiledMap->getObjectGroup("sprites");
	auto weapon = objectGroup->getObject("weapon");
	return Vec2(weapon["x"].asFloat(), weapon["y"].asFloat());
}

bool KickMap::init()
{
	if (Node::init() == false)
		return false;

	_tiledMap = experimental::TMXTiledMap::create("tiled/m1.tmx");
	ValueVector grounds = _tiledMap->getObjectGroup("grounds")->getObjects();
	for (auto obj : grounds)
	{
		ValueMap& ground = obj.asValueMap();
		auto groundX = ground["x"].asFloat();
		auto groundY = ground["y"].asFloat();
		auto groundW = ground["width"].asFloat();
		auto groundH = ground["height"].asFloat();
		PhysicsBody * phy = PhysicsBody::createBox(Size(groundW, groundH));
		phy->setDynamic(false);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(groundX, groundY));
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setContentSize(Size(groundW, groundH));
		sp->setPhysicsBody(phy);
		_tiledMap->addChild(sp); 
	}
	
	addChild(_tiledMap);
	return true;
}
