#include "KickFaceScene.h"
#include "Background.h"
#include "SimpleAudioEngine.h"
#include "Background.h"
#include "BeeSprite.h"
#include "BodyContactHelper.h"
#include "FaceSprite.h"
#include "KickMap.h"
#include "KFCommonDefinition.h"


KickFaceScene::KickFaceScene():
_hammer(nullptr),
_face(nullptr),
_tileMap(nullptr),
_background(nullptr),
_boundary(nullptr)
{
}


KickFaceScene::~KickFaceScene()
{
	_background->removeAllChildren();
	this->Scene::removeAllChildren();
}

bool KickFaceScene::onTouchHammerBegan(cocos2d::Touch * touch, cocos2d::Event * e)
{
	const auto location = this->convertToWorldSpace(touch->getLocation());
	auto arr = getPhysicsWorld()->getShapes(location);

	PhysicsBody* body = nullptr;
	for (auto& obj : arr)
	{
		if ((obj->getBody()->getTag() & HAMMER_BODY_TAG) != 0)
		{
			body = obj->getBody();
			break;
		}
	}

	if (body != nullptr)
	{
		Node* mouse = Node::create();
		auto physicsBody = PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY);
		physicsBody->setDynamic(false);
		mouse->addComponent(physicsBody);
		mouse->setPosition(location);
		this->addChild(mouse);
		PhysicsJointPin* joint = PhysicsJointPin::construct(physicsBody, body, location);
		joint->setMaxForce(20000.0f * body->getMass());
		getPhysicsWorld()->addJoint(joint);
		_mouses.insert(std::make_pair(touch->getID(), mouse));

		return true;
	}
	return false;
}

void KickFaceScene::onTouchHammerMoved(cocos2d::Touch * touch, cocos2d::Event * e)
{
	auto it = _mouses.find(touch->getID());

	if (it != _mouses.end())
	{
		it->second->setPosition(this->convertToWorldSpace(touch->getLocation()));
	}
}

void KickFaceScene::onTouchHammerEnded(cocos2d::Touch * touch, cocos2d::Event * e)
{
	auto it = _mouses.find(touch->getID());

	if (it != _mouses.end())
	{
		this->removeChild(it->second);
		_mouses.erase(it);
	}
}

bool KickFaceScene::onBodyContact(PhysicsContact & contact)
{
	switch (contact.getShapeA()->getBody()->getContactTestBitmask() |
		contact.getShapeB()->getBody()->getContactTestBitmask())
	{
	case FACE_BIT_MASK | HAMMER_BIT_MASK:
	{
		_face->showHitting();
		this->runAction(Sequence::create(DelayTime::create(0.5f),
			CallFunc::create([this]() {
			_face->showScared();
		}),
			NULL));
		break;
	}
	case FACE_BIT_MASK | GROUND_BIT_MASK:
	{
		if (contact.getShapeB()->getBody()->getTag() == BOTTOM_GROUND_TAG ||
			contact.getShapeA()->getBody()->getTag() == BOTTOM_GROUND_TAG)
		{
			kickComplete();
		}
		break;
	}
	case FACE_BIT_MASK | PROPS_BIT_MASK:
	{
		_face->showHitting();
		_background->runAction(Sequence::create(DelayTime::create(0.5f),
			CallFunc::create([this]() {
			_face->showScared();
		}),
			NULL));
		break;
	}
	case FACE_BIT_MASK | FIRE_BIT_MASK:
	{
		enterFireTime = std::chrono::steady_clock::now();
		return false;
	}
	case FACE_BIT_MASK | WATER_BIT_MASK:
	{
		_face->getPhysicsBody()->setVelocity(Vec2::ZERO);
		auto p = _face->getPosition();
		auto s = _face->getContentSize();
		addSpray(Vec2(p.x, p.y - s.height / 2));
		_face->fallInWater();
		return false;
	}
	case FACE_BIT_MASK | EDGE_BIT_MASK:
	{
		kickComplete();
		break;
	}
	case FACE_BIT_MASK | CACTUS_BIT_MASK:
	{
		_face->hitCactus();
		kickComplete();
		break;
	}
	case BEE_BIT_MASK | FACE_BIT_MASK:
	{
		BeeSprite* beeSp = BodyContactHelper::getBeeBetweenShapes(contact.getShapeA(), contact.getShapeB());
		beeSp->collidedWithFace(_face);
		break;
	}
	case FACE_BIT_MASK | PASS_BIT_MASK:
	case BEE_BIT_MASK | CACTUS_BIT_MASK:
	case HAMMER_BIT_MASK | FIRE_BIT_MASK:
	case BEE_BIT_MASK | FIRE_BIT_MASK:
	case BEE_BIT_MASK | BEE_BIT_MASK:
	case BEE_BIT_MASK | HAMMER_BIT_MASK:
	case BEE_BIT_MASK | PROPS_BIT_MASK:
	{
		return false;
	}
	default:;
	}
	return true;
}

void KickFaceScene::onBodySeparate(cocos2d::PhysicsContact & contact)
{
	switch (contact.getShapeA()->getBody()->getContactTestBitmask() |
		contact.getShapeB()->getBody()->getContactTestBitmask())
	{
	case FACE_BIT_MASK | FIRE_BIT_MASK:
	{
		exitFireTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = exitFireTime - enterFireTime;
		if (elapsed_seconds.count() > 0.1)
		{
			_face->catchFire();
		}
		break;
	}
	case FACE_BIT_MASK | PASS_BIT_MASK:
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, KickFaceScene::createKickFaceScene(levelNumber + 1)));
		break;
	}
	}
}

void KickFaceScene::kickComplete()
{
	//const auto face_vel = _face->getPhysicsBody()->getVelocity();
	_face->getPhysicsBody()->setVelocity(Vec2::ZERO);
	_face->getPhysicsBody()->setAngularVelocity(0);
	_background->stopAllActions();
	_face->showHurt();
	auto label1 = Label::createWithTTF("Kick Again", "fonts/Marker Felt.ttf", 48);
	auto item1 = MenuItemLabel::create(label1, [this](Ref* obj)
	{
		BeeSprite::clearBeesGroup();
		Director::getInstance()->replaceScene(TransitionFade::create(1, KickFaceScene::createKickFaceScene(levelNumber)));
	});
	item1->setPositionY(10);
	auto label2 = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 48);
	auto item2 = MenuItemLabel::create(label2, [](Ref* obj)
	{
		Director::getInstance()->end();
	});
	item2->setPositionY(-70);
	auto menu = Menu::create(item1, item2, NULL);

	menu->setPosition(this->convertToNodeSpace(Vec2(_visibleSize.width / 2, _visibleSize.height / 2 + 100)));
	this->addChild(menu, 1);
}

void KickFaceScene::createWorldAndMap()
{
	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -2000));
	this->getPhysicsWorld()->setSpeed(0.9);
	
	_background = Background::createBackground(WORLD_WIDTH, WORLD_HEIGHT);
	addChild(_background);
	_worldSize = _background->getContentSize();

	_boundary = Node::create();
	_boundary->setContentSize(Size(_worldSize.width, _worldSize.height + 1000));
	_boundary->setPhysicsBody(PhysicsBody::createEdgeBox(Size(_worldSize.width, _worldSize.height + 300)));
	_boundary->getPhysicsBody()->setTag(EDGE_BODY_TAG);
	/*_boundary->getPhysicsBody()->setCategoryBitmask(EDGE_CATEGORY_MASK);
	_boundary->getPhysicsBody()->setCollisionBitmask(EDGE_COLLISION_MASK);*/
	_boundary->getPhysicsBody()->setContactTestBitmask(EDGE_BIT_MASK);
	_boundary->setPosition(0, -500);
	_background->addChild(_boundary);

	_tileMap = KickMap::createKickMap(_background, this->levelNumber);
	_background->addChild(_tileMap);
}

void KickFaceScene::addFace()
{
	const auto faceStartPosition = _tileMap->getOuterSpritesStartPosition("face");
	_face = FaceSprite::create();
	_face->setPosition(faceStartPosition);
	//_face->getPhysicsBody()->setGravityEnable(false);
	_background->addChild(_face);
}

void KickFaceScene::addSpray(const Vec2& position)
{
	auto pFileLeft = FileUtils::getInstance()->getValueMapFromFile("spray.plist");
	auto emitter = ParticleSystemQuad::create(pFileLeft);
	emitter->setPositionType(ParticleSystem::PositionType::RELATIVE);
	//emitter->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
	emitter->setAutoRemoveOnFinish(true);
	emitter->setPosition(position);
	_background->addChild(emitter, 2);
}

void KickFaceScene::addKickWeapon()
{
	auto hammerPos = _tileMap->getOuterSpritesStartPosition("weapon");
	auto weaponFixPoint = Node::create();
	auto sp1PhysicsBody = PhysicsBody::createBox(Size(50, 300));
	weaponFixPoint->addComponent(sp1PhysicsBody);
	weaponFixPoint->setPosition(hammerPos.x, hammerPos.y + 100);
	sp1PhysicsBody->setGravityEnable(false);
	sp1PhysicsBody->setContactTestBitmask(PROPS_BIT_MASK);
	getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1PhysicsBody, _boundary->getPhysicsBody(), weaponFixPoint->getPosition()));
	_background->addChild(weaponFixPoint);
	
	_hammer = HammerSprite::create();
	_hammer->setPosition(hammerPos);
	auto sp2PhysicsBody = _hammer->getPhysicsBody();
	sp2PhysicsBody->setTag(HAMMER_BODY_TAG);
	sp2PhysicsBody->setContactTestBitmask(HAMMER_BIT_MASK);
	_background->addChild(_hammer);
	getPhysicsWorld()->addJoint(PhysicsJointFixed::construct(sp1PhysicsBody, sp2PhysicsBody, hammerPos));
}

void KickFaceScene::addEventHandlers()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(KickFaceScene::onTouchHammerBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(KickFaceScene::onTouchHammerMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(KickFaceScene::onTouchHammerEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _hammer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(KickFaceScene::onBodyContact, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(KickFaceScene::onBodySeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool KickFaceScene::initKickFaceScene(unsigned levelNumber)
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	this->levelNumber = levelNumber;
	_visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	createWorldAndMap();
	addFace();
	addKickWeapon();
	addEventHandlers();
	return true;
}

void KickFaceScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
  	_background->runAction(Follow::create(_face, Rect(0, 0, _worldSize.width, _worldSize.height)));
}

KickFaceScene * KickFaceScene::createKickFaceScene(unsigned levelNumber)
{
	KickFaceScene* p = new KickFaceScene();
	if (p && p->initKickFaceScene(levelNumber))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

