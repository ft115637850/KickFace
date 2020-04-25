#include "KickMap.h"

#include "BeeSprite.h"
#include "CoinSprite.h"
#include "FlagSprite.h"
#include "KFCommonDefinition.h"
#include "SnailSprite.h"

void KickMap::addSprites(TMXObjectGroup * group)
{
	ValueVector sprites = group->getObjects();
	for (auto obj : sprites)
	{
		ValueMap& spProps = obj.asValueMap();
		auto spName = spProps["name"].asString();
		Sprite* sp = nullptr;
		if (spName == "bee")
		{
			auto beeColor = spProps["color"].asInt();
			sp = BeeSprite::createBeeSprite(beeColor);
			
		}
		else if (spName == "flag")
		{
			auto flagColor = spProps["color"].asInt();
			sp = FlagSprite::createFlagSprite(flagColor);
		}
		else if (spName == "snail")
		{
			auto flagColor = spProps["color"].asInt();
			sp = SnailSprite::createSnail(flagColor);
		}
		else if (spName == "coin")
		{
			sp = CoinSprite::create();
		}
		else
		{
			continue;
		}

		sp->setPosition(Vec2(spProps["x"].asFloat(), spProps["y"].asFloat()));
		_tiledMap->addChild(sp);
	}
}

void KickMap::addFire(TMXObjectGroup * group, Background * bg)
{
	auto f = Director::getInstance()->getContentScaleFactor();
	ValueVector sprites = group->getObjects();
	for (auto obj : sprites)
	{
		ValueMap& prop = obj.asValueMap();
		auto groundX = prop["x"].asFloat();
		auto groundY = prop["y"].asFloat();
		bool isInner = prop["isInner"].asBool();

		auto pFileLeft = FileUtils::getInstance()->getValueMapFromFile("fire_background.plist");
		auto emitter = ParticleSystemQuad::create(pFileLeft);
		emitter->setPositionType(ParticleSystem::PositionType::RELATIVE);
		emitter->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
		emitter->setAutoRemoveOnFinish(true);
		if (isInner)
		{
			emitter->setPosition(Vec2(groundX, groundY));
			_tiledMap->addChild(emitter, 2);
		}
		else
		{
			emitter->setPosition(Vec2(groundX, groundY)*MAP_SCALE_FACTOR);
			emitter->setScale(MAP_SCALE_FACTOR);
			bg->addChild(emitter, 3);
		}

		auto pFileLeft2 = FileUtils::getInstance()->getValueMapFromFile("fire_foreground.plist");
		auto emitter2 = ParticleSystemQuad::create(pFileLeft2);
		emitter2->setPositionType(ParticleSystem::PositionType::RELATIVE);
		emitter2->setAutoRemoveOnFinish(true);
		if (isInner)
		{
			emitter2->setPosition(Vec2(groundX, groundY));
			_tiledMap->addChild(emitter2, 2);
		}
		else
		{
			emitter2->setPosition(Vec2(groundX, groundY)*MAP_SCALE_FACTOR);
			emitter2->setScale(MAP_SCALE_FACTOR);
			bg->addChild(emitter2, 3);
		}
	}
}

void KickMap::addFireRange(TMXObjectGroup * group)
{
	ValueVector fireRanges = group->getObjects();
	for (auto obj : fireRanges)
	{
		ValueMap& fireRange = obj.asValueMap();
		auto fireRangeX = fireRange["x"].asFloat();
		auto fireRangeY = fireRange["y"].asFloat();
		auto fireRangeW = fireRange["width"].asFloat();
		auto fireRangeH = fireRange["height"].asFloat();
		PhysicsBody * phy = PhysicsBody::createBox(Size(fireRangeW, fireRangeH), RING_MATERIAL);
		phy->setDynamic(false);
		/*phy->setCategoryBitmask(PROPS_CATEGORY_MASK);
		phy->setCollisionBitmask(PROPS_COLLISION_MASK);*/
		phy->setContactTestBitmask(FIRE_BIT_MASK);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(fireRangeX, fireRangeY));
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setContentSize(Size(fireRangeW, fireRangeH));
		sp->setPhysicsBody(phy);
		_tiledMap->addChild(sp);
	}
}

void KickMap::addWater(TMXObjectGroup * group)
{
	ValueVector waterGroup = group->getObjects();
	for (auto obj : waterGroup)
	{
		ValueMap& water = obj.asValueMap();
		auto waterX = water["x"].asFloat();
		auto waterY = water["y"].asFloat();
		auto waterW = water["width"].asFloat();
		auto waterH = water["height"].asFloat();
		PhysicsBody * phy = PhysicsBody::createBox(Size(waterW, waterH), WATER_MATERIAL);
		phy->setDynamic(false);
		/*phy->setCategoryBitmask(PROPS_CATEGORY_MASK);
		phy->setCollisionBitmask(PROPS_COLLISION_MASK);*/
		phy->setContactTestBitmask(WATER_BIT_MASK);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(waterX, waterY));
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setContentSize(Size(waterW, waterH));
		sp->setPhysicsBody(phy);
		_tiledMap->addChild(sp);
	}
}

void KickMap::addCactus(TMXObjectGroup * group)
{
	ValueVector waterGroup = group->getObjects();
	for (auto obj : waterGroup)
	{
		ValueMap& cactus = obj.asValueMap();
		auto waterX = cactus["x"].asFloat();
		auto waterY = cactus["y"].asFloat();
		auto waterW = cactus["width"].asFloat();
		auto waterH = cactus["height"].asFloat();
		PhysicsBody * phy = PhysicsBody::create();
		auto polygon = cactus["points"].asValueVector();
		auto size = polygon.size();
		Vec2* points = new Vec2[size];
		int i = 0;
		for (auto pointValue : polygon)
		{
			auto dicp = pointValue.asValueMap();
			auto x = dicp.at("x").asFloat();
			auto y = -dicp.at("y").asFloat();//y取负值
			points[i] = Vec2(x, y);
			i++;
		}
		phy->addShape(PhysicsShapePolygon::create(points, size));
		delete [] points;

		phy->setDynamic(false);
		phy->setContactTestBitmask(CACTUS_BIT_MASK);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(waterX, waterY));
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setContentSize(Size(waterW, waterH));
		sp->setPhysicsBody(phy);
		_tiledMap->addChild(sp);
	}
}

void KickMap::addPass(TMXObjectGroup * group)
{
	ValueVector waterGroup = group->getObjects();
	for (auto obj : waterGroup)
	{
		ValueMap& pass = obj.asValueMap();
		PhysicsBody * phy = PhysicsBody::createBox(Size(pass["width"].asFloat(), pass["height"].asFloat()), WATER_MATERIAL);
		phy->setDynamic(false);
		phy->setContactTestBitmask(PASS_BIT_MASK);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(pass["x"].asFloat(), pass["y"].asFloat()));
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setContentSize(Size(pass["width"].asFloat(), pass["height"].asFloat()));
		sp->setPhysicsBody(phy);
		_tiledMap->addChild(sp);
	}
}

void KickMap::addGrounds(TMXObjectGroup * group)
{
	ValueVector grounds = group->getObjects();
	for (auto obj : grounds)
	{
		ValueMap& ground = obj.asValueMap();
		auto groundX = ground["x"].asFloat();
		auto groundY = ground["y"].asFloat();
		auto groundW = ground["width"].asFloat();
		auto groundH = ground["height"].asFloat();
		auto isPolygon = ground["isPolygon"].asBool();
		PhysicsBody * phy = PhysicsBody::create();
		if (isPolygon)
		{
			auto polygon = ground["points"].asValueVector();
			auto size = polygon.size();
			Vec2* points = new Vec2[size];
			int i = 0;
			for (auto pointValue : polygon)
			{
				auto dicp = pointValue.asValueMap();
				auto x = dicp.at("x").asFloat();
				auto y = -dicp.at("y").asFloat();//y取负值
				points[i] = Vec2(x, y);
				i++;
			}
			phy->addShape(PhysicsShapePolygon::create(points, size, GROUND_MATERIAL));
			delete[] points;
		}
		else
		{
			phy->addShape(PhysicsShapeBox::create(Size(groundW, groundH), GROUND_MATERIAL));
		}
		
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
}

void KickMap::addProps(TMXObjectGroup * group)
{
	ValueVector props = group->getObjects();
	for (auto obj : props)
	{
		ValueMap& prop = obj.asValueMap();
		auto groundX = prop["x"].asFloat();
		auto groundY = prop["y"].asFloat();
		auto groundW = prop["width"].asFloat();
		auto groundH = prop["height"].asFloat();
		auto isPolygon = prop["isPolygon"].asBool();
		PhysicsBody * phy = PhysicsBody::create();
		if (isPolygon)
		{
			auto polygon = prop["points"].asValueVector();
			auto size = polygon.size();
			Vec2* points = new Vec2[size];
			int i = 0;
			for (auto pointValue : polygon)
			{
				auto dicp = pointValue.asValueMap();
				auto x = dicp.at("x").asFloat();
				auto y = -dicp.at("y").asFloat();//y取负值
				points[i] = Vec2(x, y);
				i++;
			}
			phy->addShape(PhysicsShapePolygon::create(points, size));
			delete[] points;
		}
		else
		{
			phy->addShape(PhysicsShapeBox::create(Size(groundW, groundH), PROP_MATERIAL));
		}
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
}

Vec2 KickMap::getOuterSpritesStartPosition(const std::string& spriteName) const
{
	auto objectGroup = _tiledMap->getObjectGroup("sprites");
	auto sp = objectGroup->getObject(spriteName);

	return Vec2(sp["x"].asFloat(), sp["y"].asFloat())*MAP_SCALE_FACTOR;
}

KickMap * KickMap::createKickMap(Background * bg, unsigned levelNumber)
{
	KickMap* p = new KickMap();
	if (p && p->initKickMap(bg, levelNumber))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool KickMap::initKickMap(Background * bg, unsigned levelNumber)
{
	if (Node::init() == false)
		return false;

	_tiledMap = TMXTiledMap::create(StringUtils::format("tiled/m%d.tmx", levelNumber));
	auto groups = _tiledMap->getObjectGroups();
	for (const auto objectGroup : groups)
	{
		if (objectGroup && objectGroup->getGroupName() == "grounds")
		{
			addGrounds(objectGroup);
		}
		else if (objectGroup && objectGroup->getGroupName() == "props")
		{
			addProps(objectGroup);
		}
		else if (objectGroup && objectGroup->getGroupName() == "sprites")
		{
			addSprites(objectGroup);
		}
		else if (objectGroup && objectGroup->getGroupName() == "fire")
		{
			addFire(objectGroup, bg);
		}
		else if (objectGroup && objectGroup->getGroupName() == "fireRange")
		{
			addFireRange(objectGroup);
		}
		else if (objectGroup && objectGroup->getGroupName() == "water")
		{
			addWater(objectGroup);
		}
		else if (objectGroup && objectGroup->getGroupName() == "cactus") 
		{
			addCactus(objectGroup);
		}
		else if (objectGroup && objectGroup->getGroupName() == "pass")
		{
			addPass(objectGroup);
		}
	}

	addChild(_tiledMap);
	setScale(MAP_SCALE_FACTOR);
	return true;
}

KickMap::~KickMap()
{
	_tiledMap->removeAllChildren();
	removeAllChildren();
}
