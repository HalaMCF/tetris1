#pragma once

#include "cocos2d.h"
USING_NS_CC;
extern int level;
class Diff : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createscene();
	virtual bool init();
	CREATE_FUNC(Diff);
	
	void Singular(Ref* obj);
private:
	EventListenerKeyboard * listener;
	int l = 1;
};
