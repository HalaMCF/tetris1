#pragma once
#include "cocos2d.h"
class muti : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createscene();
	virtual bool init();
	CREATE_FUNC(muti);

	void menuCallBack(Ref*obj);
private:
	int ReLevel, MyLevel;
	int ReScore, MyScore;
	int ReLine, MyLine;
	float ReSpeed, MySpeed;
};
