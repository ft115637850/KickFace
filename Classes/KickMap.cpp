#include "KickMap.h"

#include "BeeSprite.h"
#include "FaceSprite.h"
#include "KFCommonDefinition.h"

void KickMap::addBees()
{
	ValueVector sprites = _tiledMap->getObjectGroup("sprites")->getObjects();
	for (auto obj : sprites)
	{
		ValueMap& prop = obj.asValueMap();
		auto spName = prop["name"].asString();
		auto groundX = prop["x"].asFloat();
		auto groundY = prop["y"].asFloat();
		if (spName == "bee")
		{
			auto beeColor = prop["color"].asInt();
			auto sp = BeeSprite::createBeeSprite(beeColor);
			sp->setPosition(Vec2(groundX, groundY));
			_tiledMap->addChild(sp);
		}
	}
}

Vec2 KickMap::getOuterSpritesStartPosition(const std::string& spriteName)
{
	auto objectGroup = _tiledMap->getObjectGroup("sprites");
	auto sp = objectGroup->getObject(spriteName);

	return Vec2(sp["x"].asFloat(), sp["y"].asFloat())*MAP_SCALE_FACTOR;
}

bool KickMap::init()
{
	if (Node::init() == false)
		return false;

	_tiledMap = TMXTiledMap::create("tiled/m1.tmx");
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
		/*phy->setCategoryBitmask(GROUND_CATEGORY_MASK);
		phy->setCollisionBitmask(GROUND_COLLISION_MASK);*/
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
		/*phy->setCategoryBitmask(PROPS_CATEGORY_MASK);
		phy->setCollisionBitmask(PROPS_COLLISION_MASK);*/
		phy->setContactTestBitmask(PROPS_BIT_MASK);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(groundX, groundY));
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setContentSize(Size(groundW, groundH));
		sp->setPhysicsBody(phy);
		_tiledMap->addChild(sp);
	}

	addBees();
	addChild(_tiledMap);
	setScale(MAP_SCALE_FACTOR);
	return true;
}
