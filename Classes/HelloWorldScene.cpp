/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

#include "Background.h"
#include "SimpleAudioEngine.h"
#include "Background.h"
#include "FaceSprite.h"
#include "KickMap.h"
#include "HammerSprite.h"

USING_NS_CC;

//#define EDGE_BIT_MASK	0b0001
#define FACE_BIT_MASK	0b1000
#define HAMMER_BIT_MASK	0b0100
#define HAMMER_BODY_TAG 0x80

bool HelloWorld::onTouchHammerBegan(cocos2d::Touch * touch, cocos2d::Event * e)
{
	const auto location = touch->getLocation();
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
		joint->setMaxForce(5000.0f * body->getMass());
		getPhysicsWorld()->addJoint(joint);
		_mouses.insert(std::make_pair(touch->getID(), mouse));

		return true;
	}
	return false;
}

void HelloWorld::onTouchHammerMoved(cocos2d::Touch * touch, cocos2d::Event * e)
{
	auto it = _mouses.find(touch->getID());

	if (it != _mouses.end())
	{
		it->second->setPosition(touch->getLocation());
	}
}

void HelloWorld::onTouchHammerEnded(cocos2d::Touch * touch, cocos2d::Event * e)
{
	auto it = _mouses.find(touch->getID());

	if (it != _mouses.end())
	{
		this->removeChild(it->second);
		_mouses.erase(it);
	}
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics())
    {
        return false;
    }
	
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -1000));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto _tileMap = KickMap::create();
	auto startPos = _tileMap->getFaceStartPosition();
	float bgPosY = -1 * (startPos.y - visibleSize.height * 3 / 5);
	_tileMap->setPosition(0, bgPosY);

	auto bg = Background::create();
	bg->setPosition(0, bgPosY);
	addChild(bg);
	addChild(_tileMap);

	auto bgSize = bg->getContentSize();
	auto bounds = Node::create();
	bounds->setContentSize(bgSize);
	bounds->setPhysicsBody(PhysicsBody::createEdgeBox(bgSize));
	//bounds->getPhysicsBody()->setContactTestBitmask(EDGE_BIT_MASK);
	bounds->setPosition(bg->getPosition());
	addChild(bounds);
	
	auto face = FaceSprite::create();
	face->setPosition(startPos.x, visibleSize.height * 3 / 5 + 30);
	face->getPhysicsBody()->setContactTestBitmask(FACE_BIT_MASK);
	addChild(face);

	auto hammerPos = _tileMap->getWeaponPosition();	
	auto weaponFixPoint = Node::create();
	auto sp1PhysicsBody = PhysicsBody::createBox(Size(10, 20));
	weaponFixPoint->addComponent(sp1PhysicsBody);
	weaponFixPoint->setPosition(hammerPos.x, (hammerPos.y - startPos.y) + visibleSize.height * 3 / 5 + 100);
	getPhysicsWorld()->addJoint(PhysicsJointPin::construct(sp1PhysicsBody, bounds->getPhysicsBody(), weaponFixPoint->getPosition()));
	addChild(weaponFixPoint);
	
	auto hammer = HammerSprite::create();
	hammer->setPosition(hammerPos.x, (hammerPos.y - startPos.y) + visibleSize.height * 3 / 5);
	auto sp2PhysicsBody = hammer->getPhysicsBody();
	sp2PhysicsBody->setTag(HAMMER_BODY_TAG);
	sp2PhysicsBody->setContactTestBitmask(HAMMER_BIT_MASK);
	addChild(hammer);

	PhysicsJointFixed* joint = PhysicsJointFixed::construct(sp1PhysicsBody, sp2PhysicsBody, Vec2(hammerPos.x, (hammerPos.y - startPos.y) + visibleSize.height * 3 / 5 + 90));
	getPhysicsWorld()->addJoint(joint);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchHammerBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchHammerMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchHammerEnded, this);
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, hammer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this, face, bgPosY, bgSize](PhysicsContact& contact) {
		switch (contact.getShapeA()->getBody()->getContactTestBitmask() |
			contact.getShapeB()->getBody()->getContactTestBitmask())
		{
		case FACE_BIT_MASK | HAMMER_BIT_MASK:
			this->runAction(Follow::create(face, Rect(0, bgPosY, bgSize.width, bgSize.height)));
			break;
		default: ;
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

