#include <stdio.h>
#include "Muti.h"
#include"MainMenu.h"
#include"Remote.h"
USING_NS_CC;
int i;
Scene* muti::createScene()
{
	auto scene = Scene::create();
	auto layer = muti::create();
	scene->addChild(layer);

	return scene;
}

bool muti::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(24);

	MenuItemFont *R = MenuItemFont::create("Ready", CC_CALLBACK_1(muti::Ready, this));
	MenuItemFont *Back = MenuItemFont::create("Back", CC_CALLBACK_1(muti::Back, this));


	Menu* menu = Menu::create(R, Back, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);
	return true;
}
void muti::Ready(cocos2d::Ref* pSender)
{
	auto client = Client::create();
	this->addChild(client);
	if (i == 1)
	{
		auto re = Net::createScene();
		Director::getInstance()->pushScene(re);
	}
}
void muti::Back(cocos2d::Ref* pSender)
{
	auto re = MainMenu::createScene();
	Director::getInstance()->pushScene(re);
}