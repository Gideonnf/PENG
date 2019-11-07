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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
private:
	// EX 2
	float m_inputMovementAxis;
	float m_charMoveSpeed;
	Node* m_charSprite;
	bool m_gotoMouseClick;
	cocos2d::Vec2 m_mouseClickPos;
	// EX 3 PRACTICE 01
	enum MOVE_DIR
	{
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_NONE,
		NUM_DIR
	};
	cocos2d::Action* m_moveActions[NUM_DIR];
	MOVE_DIR m_currMoveAction;
	MOVE_DIR m_newMoveAction;
	Vector<SpriteFrame*> animFramesIdle;
	Vector<SpriteFrame*> animFramesMoveRight;
	Vector<SpriteFrame*> animFramesMoveLeft;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMouseMove(cocos2d::EventMouse* event);
	void onMouseUp(cocos2d::EventMouse* event);
	void onMouseDown(cocos2d::EventMouse* event);
	void onMouseScroll(cocos2d::EventMouse* event);

	void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
