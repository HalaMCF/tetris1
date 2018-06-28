#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"
#include "Singular.h"
#include"Rank.h"
#include"Level.h"
#include"Muti.h"
class MainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuSingular(cocos2d::Ref* pSender);
	void menuMuti(cocos2d::Ref* pSender);
	void menuRank(cocos2d::Ref* pSender);
	void menuExit(cocos2d::Ref* pSender);
	CREATE_FUNC(MainMenu);
};

#endif