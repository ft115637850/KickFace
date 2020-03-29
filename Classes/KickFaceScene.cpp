#include "KickFaceScene.h"
#include "Background.h"
#include "SimpleAudioEngine.h"
#include "Background.h"
#include "FaceSprite.h"
#include "KickMap.h"
#include "ui/UIButton.h"

#define EDGE_BIT_MASK	0b00010
#define FACE_BIT_MASK	0b10000
#define HAMMER_BIT_MASK	0b01000
#define GROUND_BIT_MASK	0b00100
#define PROPS_BIT_MASK	0b00001
#define HAMMER_BODY_TAG 0x80

KickFaceScene::KickFaceScene(): _hammer(nullptr), _face(nullptr), _followAct(nullptr), _background(nullptr)
{
}


KickFaceScene::~KickFaceScene()
{

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
		const auto face_vel = _face->getPhysicsBody()->getVelocity();
		_face->getPhysicsBody()->setVelocity(face_vel*0.2);
		if (contact.getShapeB()->getBody()->getTag() == 1)
		{
			this->stopAllActions();
			_face->showHurt();
			auto label1 = Label::createWithTTF("Kick Again", "fonts/Marker Felt.ttf", 48);
			auto item1 = MenuItemLabel::create(label1, [this](Object* obj)
			{
				this->_background->stopAction(_followAct);
				Director::getInstance()->replaceScene(TransitionFade::create(1, KickFaceScene::create()));
			});
			item1->setPositionY(50);
			auto label2 = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 48);
			auto item2 = MenuItemLabel::create(label2, [](Object* obj)
			{
				Director::getInstance()->end();
			});
			item2->setPositionY(-50);
			auto menu = Menu::create(item1, item2, NULL);

			menu->setPosition(this->convertToNodeSpace(Vec2(_visibleSize.width / 2, _visibleSize.height / 2 + 100)));
			this->addChild(menu, 1);
		}
		break;
	}
	case FACE_BIT_MASK | PROPS_BIT_MASK:
	{
		_face->showHitting();
		this->runAction(Sequence::create(DelayTime::create(0.5f),
			CallFunc::create([this]() {
				_face->showScared();
			}),
			NULL));
		break;
	}
	default:;
	}
	return true;
}

bool KickFaceScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -1000));

	_visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_background = Background::createBackground(0, 0);
	addChild(_background);
	_worldSize = _background->getContentSize();

	auto bounds = Node::create();
	bounds->setContentSize(_worldSize);
	bounds->setPhysicsBody(PhysicsBody::createEdgeBox(_worldSize));
	bounds->getPhysicsBody()->setContactTestBitmask(EDGE_BIT_MASK);
	bounds->setPosition(_background->getPosition());
	_background->addChild(bounds);

	auto _tileMap = KickMap::create();
	const auto faceStartPosition = _tileMap->getFaceStartPosition();
	_background->addChild(_tileMap);


	_face = FaceSprite::create();
	_face->setPosition(faceStartPosition);
	_face->getPhysicsBody()->setContactTestBitmask(FACE_BIT_MASK);
	//face->getPhysicsBody()->setGravityEnable(false);
	_background->addChild(_face);

	auto hammerPos = _tileMap->getWeaponPosition();
	auto weaponFixPoint = Node::create();
	auto sp1PhysicsBody = PhysicsBody::createBox(Size(50, 300));
	weaponFixPoint->addComponent(sp1PhysicsBody);
	weaponFixPoint->setPosition(hammerPos.x, hammerPos.y + 100);
	sp1PhysicsBody->setVelocity(Vec2::ZERO);
	getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1PhysicsBody, bounds->getPhysicsBody(), weaponFixPoint->getPosition()));
	_background->addChild(weaponFixPoint);

	_hammer = HammerSprite::create();
	_hammer->setPosition(hammerPos);
	auto sp2PhysicsBody = _hammer->getPhysicsBody();
	sp2PhysicsBody->setTag(HAMMER_BODY_TAG);
	sp2PhysicsBody->setContactTestBitmask(HAMMER_BIT_MASK);
	sp1PhysicsBody->setVelocity(Vec2::ZERO);
	_background->addChild(_hammer);

	PhysicsJointFixed* joint = PhysicsJointFixed::construct(sp1PhysicsBody, sp2PhysicsBody, hammerPos);
	getPhysicsWorld()->addJoint(joint);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(KickFaceScene::onTouchHammerBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(KickFaceScene::onTouchHammerMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(KickFaceScene::onTouchHammerEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _hammer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(KickFaceScene::onBodyContact, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	return true;
}

void KickFaceScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	_background->runAction(Follow::create(_face, Rect(0, 0, _worldSize.width, _worldSize.height)));
}

