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
#include "SimpleAudioEngine.h"

using namespace cocos2d;

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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1); */

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                            origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //}
	// Create a playing size
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	// Add sprites into the screen
	for (int i = 0; true; ++i)
	{
		const float SIZE = 5.f;
		auto nodeItems = Node::create();
		nodeItems->setName("nodeItems");
		// Create a sprite object to load the image
		auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
		// Set anchor point and position of your object
		sprite->setAnchorPoint(Vec2::ZERO);
		float offset = i * SIZE;
		sprite->setPosition(i * sprite->getContentSize().width, visibleSize.height / 2);
		// Add object into the node container
		nodeItems->addChild(sprite, 0);
		this->addChild(nodeItems, 1);
		if (i * sprite->getContentSize().width >= visibleSize.width)
			break;
	}
	// Adding movable objects
	// Create node containter for sprites
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");
	// Load the sprite
	auto mainSprite = Sprite::create("Blue_Front1.png");
	mainSprite->setAnchorPoint(Vec2::ZERO);
	mainSprite->setPosition(100, visibleSize.height / 2 + spriteNode->getContentSize().height);
	mainSprite->setName("mainSprite");
	// Add the sprite into the scene
	spriteNode->addChild(mainSprite, 1);
	this->addChild(spriteNode, 1);
	m_charSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
	// LOAD SPRITEFRAMES
	for each (Action* var in m_moveActions)
	{
		var = nullptr;
	}
	// MOVE_NONE
	{
		animFramesIdle.reserve(4);
		animFramesIdle.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
		animFramesIdle.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		animFramesIdle.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
		animFramesIdle.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		// LOAD ANIMATION
		Animation* animation = Animation::createWithSpriteFrames(animFramesIdle, 1.f);
		Animate* animateIdle = Animate::create(animation);
		m_moveActions[MOVE_NONE] = RepeatForever::create(animateIdle);
		//m_charSprite->runAction(m_moveActions[MOVE_NONE]);
		m_currMoveAction = MOVE_NONE;
		m_newMoveAction = MOVE_NONE;
	}
	// MOVE LEFT
	{
		animFramesMoveLeft.reserve(4);
		animFramesMoveLeft.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 65, 81)));
		animFramesMoveLeft.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
		animFramesMoveLeft.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 65, 81)));
		animFramesMoveLeft.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
		// LOAD ANIMATION
		Animation* animation = Animation::createWithSpriteFrames(animFramesMoveLeft, 1.f);
		Animate* animateIdle = Animate::create(animation);

		m_moveActions[MOVE_LEFT] = RepeatForever::create(animateIdle);
	}
	// MOVE RIGHT
	{
		animFramesMoveRight.reserve(4);
		animFramesMoveRight.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 65, 81)));
		animFramesMoveRight.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));
		animFramesMoveRight.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 65, 81)));
		animFramesMoveRight.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));	
		// LOAD ANIMATION
		Animation* animation = Animation::createWithSpriteFrames(animFramesMoveRight, 1.f);
		Animate* animateIdle = Animate::create(animation);
		m_moveActions[MOVE_RIGHT] = RepeatForever::create(animateIdle);
	}
	// Create keyboard event
	// ON KEY PRESSED
	{
		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	// ON KEY RELEASED
	{
		auto listener = EventListenerKeyboard::create();
		listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	// MOUSE EVENTS
	{
		// On MOUSE MOVE
		auto listener = EventListenerMouse::create();
		listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
		// On Mouse Up
		listener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
		// On Mouse Down
		listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
		// On Mouse Scroll
		listener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	// TOUCH EVENTS (singular touches)
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [](Touch* touch, Event* event)
		{
			return true;
		};
		listener->onTouchMoved = [](Touch* touch, Event* event)
		{
			return true;
		};
		listener->onTouchEnded = [](Touch* touch, Event* event)
		{
			return true;
		};
		listener->onTouchCancelled = [](Touch* touch, Event* event)
		{
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	// TOUCH EVENTS (multiple touches)
	{
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = [](const std::vector<Touch*>& touches, Event* event)
		{
			return true;
		};
		listener->onTouchesMoved = [](const std::vector<Touch*>& touches, Event* event)
		{
			return true;
		};
		listener->onTouchesEnded = [](const std::vector<Touch*>& touches, Event* event)
		{
			return true;
		};
		listener->onTouchesCancelled = [](const std::vector<Touch*>& touches, Event* event)
		{
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	// ACCELEROMETER
	{
		auto listener = EventListenerAcceleration::create([](Acceleration* acceleration, Event* event)
			{

			}
		);
	}

	// Initialize member variables
	m_charMoveSpeed = 50.f;
	
	m_gotoMouseClick = false;
	m_mouseClickPos.setZero();
	// Call render
	this->scheduleUpdate();
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_inputMovementAxis += 1.f;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_inputMovementAxis += -1.f;
	}

	// When you stop an action by tag, you delete it
	//if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	//	this->getChildByName("spriteNode")->getChildByName("mainSprite")->stopAllActions();
		//m_charSprite->stopActionByTag(m_animAction);
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_inputMovementAxis -= 1.f;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_inputMovementAxis -= -1.f;
	}
}

void HelloWorld::onMouseMove(EventMouse* event)
{

}

void HelloWorld::onMouseUp(cocos2d::EventMouse* event)
{
	
}

void HelloWorld::onMouseDown(cocos2d::EventMouse* event)
{
	m_gotoMouseClick = true;
	m_mouseClickPos.set(event->getCursorX(), event->getCursorY());

	Animation* animation = Animation::createWithSpriteFrames(animFramesIdle, 1.f);
	Animation* animation2 = Animation::createWithSpriteFrames(animFramesIdle, 1.f);
	Animate* animateIdle = Animate::create(animation);
	Animate* animateIdle2 = Animate::create(animation2);
	auto mySpawn = Spawn::createWithTwoActions(animateIdle, animateIdle2);
	auto myCallbak = CallFunc::create([]()
		{
			log("hello");
		});
	auto mySequence = Sequence::create(mySpawn, myCallbak, nullptr);
	m_charSprite->runAction(mySequence);
}

void HelloWorld::onMouseScroll(cocos2d::EventMouse* event)
{
}

void HelloWorld::update(float delta)
{
	MoveBy* moveEvent;
	if (!m_gotoMouseClick)
	{
		moveEvent = MoveBy::create(0.0f, Vec2(m_inputMovementAxis * m_charMoveSpeed * delta, 0.f));
	}
	else
	{
		Vec2 distanceRemaining = m_mouseClickPos - m_charSprite->getPosition();
		if (distanceRemaining.lengthSquared() <= m_charMoveSpeed * delta * m_charMoveSpeed * delta)
		{
			moveEvent = MoveBy::create(0.0f, m_mouseClickPos - m_charSprite->getPosition());
			m_gotoMouseClick = false;
		}
		else
		{
			Vec2 movementDelta = (m_mouseClickPos - m_charSprite->getPosition()).getNormalized() * m_charMoveSpeed * delta;
			moveEvent = MoveBy::create(0.0f, movementDelta);
		}
	}
	
	// NOTE :same can be applied to different sprites using CloneBy or reverse
	// Take note of internal state of action
	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//mainSprite->runAction(sequence);
	m_charSprite->runAction(moveEvent);
}
