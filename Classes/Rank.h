#pragma once

#include "cocos2d.h"
#include<vector>
using namespace std;
class Rank : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createscene();
	virtual bool init();

	CREATE_FUNC(Rank);
	void menuCallBack(Ref* obj);
};
