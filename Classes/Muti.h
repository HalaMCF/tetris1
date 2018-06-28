#pragma once
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "json/document.h"
#include"client.h"
USING_NS_CC_EXT;
class muti : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();



	CREATE_FUNC(muti);

	void Ready(cocos2d::Ref* pSender);
	void Back(cocos2d::Ref* pSender);

};