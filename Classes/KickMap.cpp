#include "KickMap.h"

#define GROUND_BIT_MASK	0b00100
#define PROPS_BIT_MASK	0b00001

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

	_tiledMap = experimental::TMXTiledMap::create("tiled/lm1.tmx");
	ValueVector grounds = _tiledMap->getObjectGroup("grounds")->getObjects();
	for (auto obj : grounds)
	{
		ValueMap& ground = obj.asValueMap();
		auto groundX = ground["x"].asFloat();
		auto groundY = ground["y"].asFloat();
		auto groundW = ground["width"].asFloat();
		auto groundH = ground["height"].asFloat();
		
		PhysicsBody * phy = PhysicsBody::createBox(Size(groundW, groundH), PhysicsMaterial(1.0f, 0.1f, 1.0f));
		if (!ground["tag"].isNull())
		{
			phy->setTag(ground["tag"].asInt());
		}

		phy->setDynamic(false);
		phy->setContactTestBitmask(GROUND_BIT_MASK);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(groundX, groundY));
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setContentSize(Size(groundW, groundH));
		sp->setPhysicsBody(phy);
		_tiledMap->addChild(sp); 
	}
	
	ValueVector props = _tiledMap->getObjectGroup("props")->getObjects();
	for (auto obj : props)
	{
		ValueMap& prop = obj.asValueMap();
		auto groundX = prop["x"].asFloat();
		auto groundY = prop["y"].asFloat();
		auto groundW = prop["width"].asFloat();
		auto groundH = prop["height"].asFloat();
		PhysicsBody * phy = PhysicsBody::createBox(Size(groundW, groundH), PhysicsMaterial(1.0f, 1.0f, 1.0f));
		phy->setDynamic(false);
		phy->setContactTestBitmask(PROPS_BIT_MASK);
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
